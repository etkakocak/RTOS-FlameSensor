# Real-time Hardware Project with RTOS

### Overview
A ```real-time hardware``` application was implemented using the Raspberry Pi Pico 2040 microcontroller in this project. The objective of the project is to create a flame detector system using a flame sensor, a button, and an LED. The LED turns on when the sensor detects flame, and the LED turns off when the button is pressed. The LED represents whether the fire is under control or not. Three tasks were created to manage these processes in real-time using RTOS: controlling the flame sensor, monitoring the button status, and managing the LED. Later, the same project was replicated with ```MicroPython``` without using RTOS.  

[Click to see the image of the circuit.](images/circuit.png)   
*Pico H was used to develop a C program with FreeRTOS, and Pico W was used to develop a MicroPython program.*  

### Requirements
Real-time requirements require certain operations to be performed within precise periods. For example, the LED should turn on immediately when a flame is detected, and the LED should turn off immediately when the button is pressed. Adhering to these time constraints is critical for safety and performance.  
* This RTOS-based flame sensor project requires a **Raspberry Pi Pico** running the **Pico SDK**.  
* Additionally, you must install the **FreeRTOS library** to ensure proper execution of real-time tasks.  
--- 
**RTOS is necessary to meet these requirements:**
* Task priority: RTOS ensures the timely execution of critical tasks by managing tasks with different priorities.
* Time intervals: Enables tasks to run at specific intervals and continue without interruption.
* Resource management: Regulates the effective use of system resources such as memory and processor, so that the system operates stable and reliably.
