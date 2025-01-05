cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK import
include(pico_sdk_import.cmake)

# Set the project name and languages
project(test_project C CXX ASM)

# Set the C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add FreeRTOS include directories
include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/portable/GCC/ARM_CM0)
include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/conf)

# Add FreeRTOS source files
set(FREERTOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/tasks.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/queue.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/list.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/timers.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/event_groups.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

# Add the executable
add_executable(pio_blink
    main.c
    ${FREERTOS_SOURCES}
)

# Include the blink.pio program
pico_generate_pio_header(pio_blink ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Link the Pico standard library, hardware_pio library, and FreeRTOS library
target_link_libraries(pio_blink PRIVATE pico_stdlib hardware_pio)

# Enable additional outputs like map/bin/hex/uf2
pico_add_extra_outputs(pio_blink)
