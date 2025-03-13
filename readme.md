# STM32H745I-Disco with ESP32-CAM and FreeRTOS ML Integration

This repository demonstrates how to integrate an ESP32-CAM module with the STM32H745I-DISCO board via SPI, using FreeRTOS for task management and incorporating machine learning (ML) functionalities. The project is designed for applications such as real-time image processing, computer vision, and IoT-based ML inference.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware Setup](#hardware-setup)
- [Software Components](#software-components)
- [Getting Started](#getting-started)
- [Usage](#usage)

## Overview
This project connects an ESP32-CAM module to an STM32H745I-DISCO board using SPI communication. It leverages FreeRTOS to manage concurrent tasks and integrates a machine learning module to process data captured by the camera. The setup is ideal for projects that require real-time processing and ML inference on embedded systems.

## Features
- **SPI Communication:** Establishes a reliable link between the STM32 board and the ESP32-CAM.
- **FreeRTOS Integration:** Uses FreeRTOS for efficient multitasking and resource management.
- **Machine Learning Capabilities:** Integrates ML functionality for on-board data processing and inference.
- **Modular Design:** Structured code that allows for easy extension and customization.
- **Demo Applications:** Example tasks to demonstrate camera data acquisition, ML processing, and communication.

## Hardware Setup
- **STM32H745I-DISCO Board:** Serves as the main processing unit.
- **ESP32-CAM Module:** Provides image capture capabilities.
- **SPI Connections:** Ensure proper wiring between the STM32 board and the ESP32-CAM. Verify pin configurations and signal integrity.
- **Power Supply:** Confirm that both boards are provided with appropriate voltage and current as specified in their datasheets.

## Software Components
- **FreeRTOS:** A real-time operating system managing multiple concurrent tasks.
- **SPI Driver:** Custom implementation to handle communication between the STM32 board and the ESP32-CAM.
- **Machine Learning Module:** Incorporates ML algorithms and inference code to process camera data (customizable based on the chosen ML library).
- **Board Support Package (BSP):** Contains drivers and utilities tailored for the STM32H745I-DISCO board.

## Getting Started

### Prerequisites
- **Development Environment:** STM32CubeIDE or another compatible IDE.
- **Toolchain:** ARM Cortex-M toolchain (GCC, Keil, etc.).
- **FreeRTOS:** Already integrated into the repository.
- **ML Library:** Ensure the ML library dependencies are installed and supported by your toolchain.

### Installation
1. **Clone the Repository:**
    ```bash
    git clone https://github.com/yourusername/your-repo-name.git
    cd your-repo-name
    ```
2. **Open the Project:** Launch STM32CubeIDE (or your preferred IDE) and open the project.
3. **Configure SPI Settings:** Modify the SPI configuration in `spi_config.c` (or the equivalent file) as needed.
4. **Build the Project:** Compile the project using your development environment.
5. **Flash the Firmware:** Upload the firmware to your STM32H745I-DISCO board using an appropriate programmer/debugger.

## Usage
- **Initialization:** On startup, the STM32 board initializes the SPI interface to establish communication with the ESP32-CAM.
- **Task Scheduling:** FreeRTOS handles tasks for camera data acquisition, ML inference, and any additional application logic.
- **Monitoring:** Use the serial console or onboard debugging tools to monitor system logs and ML inference results.
- **Customization:** Adjust the ML model or modify FreeRTOS tasks to suit your specific application requirements.
