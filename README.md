# Water Quality Monitor

Real-time water quality monitoring system designed for community access to clean water. This device measures Total Dissolved Solids (TDS), pH, and Turbidity using an ESP32 microcontroller. It logs data to an SD card for historical tracking and provides local visual and audio feedback.

## Features

*   **Real-time Monitoring:** Continuously tracks TDS, pH, and Turbidity levels.
*   **Data Filtering:** Implements a rolling average algorithm to smooth out sensor noise and prevent false positives.
*   **Local Display:** Uses a 16x2 I2C LCD to display metrics locally.
*   **Alert System:** Triggers an active buzzer if water quality falls below safe thresholds.
*   **Data Logging:** Automatically appends readings to a CSV file on a MicroSD card every 10 seconds.

## Hardware Requirements

*   ESP32 Development Board
*   Analog TDS Sensor
*   Analog pH Sensor
*   Analog Turbidity Sensor
*   16x2 I2C LCD
*   MicroSD Card Module (SPI)
*   Active Buzzer

## Software Stack

*   **Environment:** PlatformIO / Arduino framework
*   **Language:** C++
*   **Libraries:** `Wire`, `LiquidCrystal_I2C`, `SPI`, `SD`

## Setup Instructions

1.  Open the project in PlatformIO.
2.  Install the required dependencies listed in `platformio.ini`.
3.  Upload the firmware to your ESP32 board.
4.  Ensure the SD card is formatted to FAT32 before inserting it into the module.
