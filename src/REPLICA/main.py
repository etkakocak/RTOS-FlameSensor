import machine
import time

# GPIO Pins
FLAME_SENSOR_PIN = 28
BUTTON_PIN = 15
LED_PIN = 3

# Initialize GPIOs
flame_sensor = machine.Pin(FLAME_SENSOR_PIN, machine.Pin.IN)
button = machine.Pin(BUTTON_PIN, machine.Pin.IN, machine.Pin.PULL_DOWN)
led = machine.Pin(LED_PIN, machine.Pin.OUT)

# Global variable to track the LED state
led_on = False

def check_flame_sensor():
    global led_on
    for i in range(1):
        flame_detected = flame_sensor.value()
        if flame_detected == 0:
            led_on = True
            print("Fire detected")

def check_button():
    global led_on
    for i in range(1):
        button_pressed = button.value()
        if button_pressed == 1:
            led_on = False
            print("Fire under control")

def control_led():
    global led_on
    for i in range(1):
        if led_on:
            led.value(1)
            print("LED is on")
        else:
            led.value(0)

# Main loop
def main():
    # Start the tasks
    while True:
        check_flame_sensor()
        time.sleep(0.05)
        check_button()
        time.sleep(0.05)
        control_led()
        time.sleep(0.05)

main()
