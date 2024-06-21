# Power Window Control System

This project implements a power window control system for the front passenger door, with controls available from both the passenger and driver control panels. The system uses FreeRTOS and includes features such as manual and automatic window operation, window lock, and jam protection.

## System Features

### Manual Open/Close Function
- The window opens or closes while the power window switch is continuously pushed or pulled.
- The window stops moving when the switch is released.

### One Touch Auto Open/Close Function
- A short push or pull of the power window switch will fully open or close the window.

### Window Lock Function
- When the window lock switch is turned on, the opening and closing of all windows except the driver’s window is disabled.

### Jam Protection Function
- During one-touch auto close operation, the window stops and moves downward for about 0.5 seconds if an obstacle is detected.

## Hardware Components
- **Microcontroller**: Tiva C
- **Limit Switches**: Two (top and bottom limits)
- **DC Motor**: To control the window operation
- **Push Buttons**: For window up/down operation on both passenger and driver sides
- **ON/OFF Switch**: For locking the passenger panel from the driver panel

## System Implementation

### FreeRTOS Tasks
- **Manual Control Task**: Handles manual open/close operations.
- **Auto Control Task**: Manages one-touch auto open/close functions.
- **Lock Control Task**: Controls the window lock functionality.
- **Jam Protection Task**: Detects obstacles and activates jam protection.

### Finite State Machine
The control logic is implemented using a Finite State Machine (FSM) with transitions based on the inputs from the limit switches, push buttons, and obstacle detection.

### Limit Switches
- **Top Limit Switch**: Detects when the window is fully closed.
- **Bottom Limit Switch**: Detects when the window is fully open.

### Obstacle Detection
- **Jam Detection Button**: Simulates obstacle detection by indicating jamming.

## System Operation

### Manual Operation
1. **Push/Pull Button**: Move the window up/down while the button is pressed.
2. **Release Button**: Stop the window movement.

### Automatic Operation
1. **Short Push/Pull Button**: Fully open/close the window with a single press.

### Window Lock
1. **ON/OFF Switch**: Lock/unlock the passenger panel from the driver panel.

### Jam Protection
1. **Obstacle Detection**: Stop and reverse the window if an obstacle is detected during auto close.

## Project Setup

### Hardware Connections
- **DC Motor**: Connect to motor driver controlled by the microcontroller.
- **Limit Switches**: Connect to GPIO pins for detecting top and bottom limits.
- **Push Buttons**: Connect to GPIO pins for manual control on both driver and passenger sides.
- **ON/OFF Switch**: Connect to a GPIO pin for window lock control.
- **Jam Detection Button**: Connect to a GPIO pin to simulate obstacle detection.

### Software Implementation
1. **FreeRTOS**: Use FreeRTOS for task management.

### Code Structure
- **main.c**: Initializes the system, creates FreeRTOS tasks.
- **tasks.c**: Implements FreeRTOS tasks for manual control, auto control, lock control, and jam protection.
- **fsm.c**: Contains the FSM logic for window control.
- **gpio.c**: GPIO driver for handling input/output operations.
- **motor.c**: DC motor driver for controlling the window motor.
- **switches.c**: Handles limit switch and button inputs.
- **FreeRTOSConfig.h**: FreeRTOS configuration file.

