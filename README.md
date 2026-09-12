# Water Quality Monitor

An embedded monitoring solution for continuous real-time analysis of water parameters, logging data directly to solid-state storage.

![C++](https://img.shields.io/badge/C++-11-00599C?logo=c%2B%2B&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Core-F56600?logo=platformio&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-Espressif-E7352C)

## Table of Contents

1. [Features](#features)
2. [Screenshot](#screenshot)
3. [Getting Started](#getting-started)
4. [Usage](#usage)
5. [Directory Structure](#directory-structure)
6. [API Reference](#api-reference)
7. [Contributing](#contributing)
8. [License](#license)
9. [Contact](#contact)

## Features

- Comprehensive Analysis: Integrates TDS, pH, and turbidity sensors for thorough water quality assessment.
- Local Data Persistence: SD card integration for reliable, long-term environmental data logging.
- Real-Time Display: Local readout via an I2C LCD interface for immediate metric verification.
- Turborepo Integration: Structured for fast, cached firmware builds.

## Screenshot

![Sensor Array Prototype](https://via.placeholder.com/800x450?text=Sensor+Array+Prototype)

## Getting Started

### Prerequisites

- PlatformIO IDE or CLI
- Node.js (for Turborepo orchestration)
- Hardware: ESP32 development board, analog water sensors (TDS, pH, turbidity), I2C LCD, SD card module

### Installation Steps

```bash
git clone https://github.com/hamin-baek/hamin-baek.git
cd hardware/water-quality-monitor
npm install
```

### Configuration

Ensure the sensor calibration values defined in the primary header file are adjusted according to physical reference solutions before deployment.

## Usage

Build the project firmware:
```bash
npm run build
```

Upload the firmware to the attached microcontroller:
```bash
npm run upload
```

## Directory Structure

- `src/`: Sensor polling routines, data formatting, and hardware initialization logic.
- `lib/`: Custom library dependencies for specific sensor hardware.

## API Reference

The device operates autonomously, logging data in CSV format to the SD card. Consult the source code documentation for specific analog-to-digital conversion formulas and calibration procedures.

## Contributing

Any new sensor integrations must implement non-blocking read routines to maintain the integrity of the SD card write cycle.

## License

This project is licensed under the MIT License.

## Contact

Created by Achmad Miftahurrojak.
[GitHub](https://github.com/hamin-baek)
