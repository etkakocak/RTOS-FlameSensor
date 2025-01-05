#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

// GPIO Pins
#define FLAME_SENSOR_PIN 28
#define BUTTON_PIN 15
#define LED_PIN 3

uint32_t SystemCoreClock = 120000000; // Set system clock frequency

// Global variables to track the LED and Button state
volatile bool led_on = false; 
volatile bool button = false;

void FlameSensorTask(void *pvParameters) {
    while (1) {
        int64_t start_time = time_us_64();
        int flame_detected = gpio_get(FLAME_SENSOR_PIN);
        if (flame_detected == 0) {
            led_on = true;
        }
        int64_t end_time = time_us_64();
        printf("FlameSensorTask execution time: %lld us\n", end_time - start_time);
        vTaskDelay(pdMS_TO_TICKS(100)); // Check every 100 ms
    }
}

void ButtonTask(void *pvParameters) {
    while (1) {
        int64_t start_time = time_us_64();
        int button_pressed = gpio_get(BUTTON_PIN);
        if (button_pressed == 1) {
            button = true;
        } else {
            button = false;
        }

        if (button) {
            led_on = false;
        }
        int64_t end_time = time_us_64();
        printf("ButtonTask execution time: %lld us\n", end_time - start_time);
        vTaskDelay(pdMS_TO_TICKS(50)); // Check every 50 ms
    }
}

void LedTask(void *pvParameters) {
    while (1) {
        int64_t start_time = time_us_64();

        if (led_on) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }

        int64_t end_time = time_us_64();
        printf("LedTask execution time: %lld us\n", end_time - start_time);
        vTaskDelay(pdMS_TO_TICKS(50)); // Check every 50 ms
    }
}

// Dummy implementations of required FreeRTOS hooks
void vApplicationTickHook(void) {
    // Function
}

void vApplicationMallocFailedHook(void) {
    taskDISABLE_INTERRUPTS();
    for (;;) {
        // Function
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    (void) pcTaskName;
    (void) xTask;
    taskDISABLE_INTERRUPTS();
    for (;;) {
        // Function
    }
}

void vApplicationIdleHook(void) {
    // Function
}

void vStartFirstTask(void) {
    __asm volatile (
        " ldr r0, =_start_first_task     \n"
        " bx r0                         \n"
        " _start_first_task:            \n"
        " .word 0x00000000              \n"
    );
}

void SVC_Handler(void) {
    // Function
}

void PendSV_Handler(void) {
    // Function
}

int main() {
    // Initialize stdio for debug messages
    stdio_init_all();

    // Initialize GPIOs
    gpio_init(FLAME_SENSOR_PIN);
    gpio_set_dir(FLAME_SENSOR_PIN, GPIO_IN);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Set initial state of external LED to off
    gpio_put(LED_PIN, 0);
    led_on = false; 

    // Create RTOS tasks
    xTaskCreate(LedTask, "LED Task", 256, NULL, 1, NULL);
    xTaskCreate(FlameSensorTask, "Flame Sensor Task", 256, NULL, 1, NULL);
    xTaskCreate(ButtonTask, "Button Task", 256, NULL, 1, NULL);
    printf("Tasks created\n");

    // Start scheduler
    vTaskStartScheduler();
    printf("Scheduler started\n");

    // Should never reach here
    while (1);
    return 0;
}
