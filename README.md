
# EV Automotive Control System - A Smart Automotive Control SystemImplementation .                                                                                
-An Embedded Vehicle Simulation Platform Designed with **STM32F407G‑DISC1** development board.                                                                      This project demonstrates Bluetooth‑controlled motion, sensor feedback, and adaptive automotive behaviour using bare‑metal programming.                         -It is Completely based On Peripheral & Protocols Project.                                                                                                      

## Motivation
-I started this project one month ago to gain hands‑on knowledge of STM32 peripherals and communication protocols using bare‑metal coding. By implementing UART,   SPI, I2C, ADC, Timers, and GPIO drivers directly at the register level Programming , I strengthened my understanding of Embedded Systems and real‑time control.  
-This project was a practical way to apply my learning and showcase my ability to design a complete automotive control system from scratch.

------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Project Overview
- Bluetooth‑controlled embedded vehicle simulation platform.
- Integrates **motor control**, **wireless communication**, **sensor feedback**, and **visual status indication**.
- Controlled via a mobile app (HC‑06 Bluetooth module).
- Implements **super‑loop architecture** with deterministic scheduling (no RTOS).

---

## User Capabilities
- Power ON/OFF remotely.
- Drive forward, backward, left, right.
- Smooth stop without jerks.
- LCD status display (system state, motion, sensor feedback).
- Automatic safety warnings during aggressive motion.
- Adaptive headlights (LDR sensor).
- Turn indicators blink during rotation.

---
## Mobile Application
The vehicle is controlled through a custom mobile app via Bluetooth (HC‑06 module).  
The app provides an intuitive interface with the following features:

- **Power Button** → Toggle system ON/OFF  
- **Directional Buttons** → Forward, Backward, Left, Right  
- **Stop Button** → Smooth deceleration without jerks  
- **Serial Terminal** → Displays live sensor data and system feedback  

Each button sends a single ASCII character over Bluetooth to the STM32F407G‑DISC1 board:
| Command | Action |
|---------|--------|
| `S` | Power ON (Active Mode) |
| `d` | Power OFF (Standby Mode) |
| `2` | Forward motion |
| `4` | Backward motion |
| `1` | Right pivot |
| `3` | Left pivot |
| `0` | Smooth stop |

---

## Functional Requirements
- Gradual acceleration/deceleration (PWM controlled).
- Safe stopped state on startup.
- Motion intensity monitoring with LCD warnings.
- Automatic headlights via LDR sensor.
- Continuous status updates on 20x4 LCD.

---

## Hardware Architecture
- **Board**: STM32F407G‑DISC1  
- **Motor Driver**: L298N  
- **Bluetooth**: HC‑06 (UART, 9600 bps)  
- **Accelerometer**: LIS302DL (SPI, onboard)  
- **Light Sensor**: LDR (ADC)  
- **LCD Display**: I2C 20x4  
- **Status LEDs**: PD12 (Right), PD13 (Left), PD14 (Headlight)

---

## Peripheral Connections
| Component | STM32 Pin | Function |
|-----------|-----------|----------|
| Left Motor PWM | PA0 | TIM2_CH1 |
| Right Motor PWM | PA1 | TIM2_CH2 |
| Motor Direction | PB0, PB1, PB10, PB11 | GPIO |
| Bluetooth TX/RX | PA2, PA3 | USART2 |
| Accelerometer SPI | PA5, PA6, PA7, PE3 | SPI1 |
| LCD I2C | PB6, PB7 | I2C1 |
| LDR Sensor | PA4 | ADC1_IN4 |
| LEDs | PD12, PD13, PD14 | GPIO |

---

## Software Implementation
- **State Machine**: Standby Mode / Active Mode.  
- **Initialisation**: RCC, GPIO, I2C, UART, SPI, TIM2, ADC.  
- **Main Loop**:
  - Continuous UART command check (~1ms).
  - Every 50ms: Read accelerometer, update LCD, blink indicators.
  - Every 100ms: Read LDR, update headlight LED.

---

## Motor Control Rules
- Acceleration in time‑controlled steps (PWM duty cycle).
- Deceleration before direction change.
- No direct reversal at full speed.

---

## Testing & Validation
1. **Boot Test**: LCD shows “System off”.  
2. **Sensor Test**: LDR controls headlight LED.  
3. **Connection Test**: Send `S` → LCD shows “System ON”.  
4. **Motor Test**: Send `2` → Forward motion, `1` → Right turn, `0` → Stop.  
5. **Accelerometer Test**: Tilt board → LCD shows motion magnitude, warnings if aggressive.
6. 

---

## Repository Structure
EV_Automotive_Control_System/
├── Header_files/        # All .h files (drivers, configs)
├── source_files/        # All .c files (implementations)
├── README.md            # Project documentation
├── .gitignore           # Ignore build artifacts


---

## Build & Run Instructions
1. Open project in **STM32CubeIDE** or your preferred toolchain.  
2. Connect STM32F407G‑DISC1 via USB.  
3. Flash the firmware to the board.  
4. Connect HC‑06 Bluetooth module to your phone.  
5. Use the mobile app to send commands (`S`, `2`, `4`, etc.).  

------
## Future Improvements
- Add FreeRTOS for task scheduling.  
- Implement CAN bus for automotive networking.  
- Expand mobile app with GUI interface.  
- Add EEPROM logging for motion history.

------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Contact
- **Name**: G VAMSHI KRISHNA
- **Email**: gvkmns@gmail.com  
- **LinkedIn**: [linkedin.com/in/gvkmns108](https://linkedin.com/in/gvkmns108)  
- **GitHub**: [github.com/gvkmns](https://github.com/gvkmns)
