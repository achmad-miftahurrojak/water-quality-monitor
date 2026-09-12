# Water Quality Monitor

A real-time water quality monitoring system designed to measure TDS, pH, and Turbidity levels for community water access.

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-lightgrey.svg)
![Language: C++](https://img.shields.io/badge/Language-C++-red.svg)

## Table of Contents
1. [Features](#features)
2. [Hardware Requirements](#hardware-requirements)
3. [Getting Started](#getting-started)
4. [Usage](#usage)
5. [Directory Structure](#directory-structure)
6. [Contributing](#contributing)
7. [Contact](#contact)

## Features
* Continuous monitoring of Total Dissolved Solids, pH, and Turbidity.
* Rolling average algorithm implementation to filter sensor noise.
* Real-time local metrics display via an I2C 16x2 LCD.
* Active buzzer activation when safe thresholds are exceeded.
* Automatic data logging to a CSV file on a MicroSD card every 10 seconds.

## Hardware Requirements
* ESP32 Development Board
* Analog TDS Sensor
* Analog pH Sensor
* Analog Turbidity Sensor
* 16x2 I2C LCD
* MicroSD Card Module (SPI)
* Active Buzzer

## Getting Started

### Prerequisites
* PlatformIO extension installed in Visual Studio Code.
* USB cable for serial communication and flashing.

### Installation
```bash
git clone https://github.com/hamin-baek/water-quality-monitor.git
cd water-quality-monitor
pio run --target upload
```

## Usage
Provide 5V and GND to the sensors and connect the analog outputs to the designated ESP32 pins. The device will automatically initialize the SD card, start the rolling average calculations, and display the metrics on the LCD.

## Directory Structure
```text
src/
  main.cpp          # Main firmware logic
include/            # Header files
lib/                # Project specific libraries
platformio.ini      # Build configuration
```

## Contributing
Contributions are welcome. Please open an issue or submit a pull request for major changes.

## Contact
Developed by Achmad Miftahurrojak.
GitHub: [hamin-baek](https://github.com/hamin-baek)

***
**Description:** Real-time ESP32 based water quality monitoring system.
**Tags:** esp32, water-quality, hardware

