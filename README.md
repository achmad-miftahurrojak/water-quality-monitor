<div align="center">

# Water Quality Monitor

<a href="README.md"><img alt="English" src="https://img.shields.io/badge/English-DFE0E5"></a> <a href="docs/README_ID.md"><img alt="Bahasa Indonesia" src="https://img.shields.io/badge/Bahasa%20Indonesia-DFE0E5"></a> <a href="docs/README_KR.md"><img alt="한국어" src="https://img.shields.io/badge/%ED%95%9C%EA%B5%AD%EC%96%B4-DFE0E5"></a>

<img alt="C++" src="https://img.shields.io/badge/C%2B%2B-11-00599C?logo=c%2B%2B&logoColor=white"> <img alt="ESP32" src="https://img.shields.io/badge/ESP32-E7352C?logo=espressif&logoColor=white"> <img alt="PlatformIO" src="https://img.shields.io/badge/PlatformIO-F56600?logo=platformio&logoColor=white">

ESP32 firmware for measuring and recording TDS, pH, and turbidity at a local water point.

[Features](#features) · [Architecture](ARCHITECTURE.md) · [Build](#build-and-upload) · [Project layout](#project-layout)

</div>

---

## Overview

The device samples three water parameters, shows the latest values on an I2C LCD, and stores timestamped readings on an SD card. MQTT and OTA hooks are available as optional integrations and remain off until local credentials and integrity settings are configured.

## Features

- TDS, pH, and turbidity sampling on an ESP32.
- Local LCD readout for field checks.
- SD card logging with RTC timestamps.
- Threshold based LED and buzzer alerts.
- Optional MQTT and OTA integration points.

## Architecture

```text
TDS / pH / turbidity sensors
              |
              v
          ESP32 node
        /      |       \
       v       v        v
     LCD    SD + RTC   MQTT
       \
        v
     LED / buzzer
```

The complete data flow and configuration boundaries are documented in [ARCHITECTURE.md](ARCHITECTURE.md).

## Build and upload

### Requirements

- PlatformIO Core or PlatformIO IDE
- ESP32 development board
- TDS, pH, and turbidity sensors
- I2C LCD, SD card module, and RTC

```bash
git clone https://github.com/achmad-miftahurrojak/water-quality-monitor.git
cd water-quality-monitor
pio run
pio run -t upload
```

Calibrate the sensor constants in the local configuration before relying on measurements. Keep private values in a local secrets header based on <code>src/secrets.example.h</code>.

## Project layout

```text
src/
├── main.cpp          # Firmware entry point
├── sensors.*         # Sensor sampling and conversion
├── storage.*         # SD and RTC logging
├── connectivity.*    # Optional MQTT / network hooks
└── alerts.*          # Local alert output
```

## License

[MIT](LICENSE) · [GitHub profile](https://github.com/achmad-miftahurrojak)
