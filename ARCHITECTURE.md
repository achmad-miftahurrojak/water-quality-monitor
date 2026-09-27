# Architecture

```text
TDS / pH / turbidity sensors
            |
            v
        ESP32 node
        /    |    \
       v     v     v
    LCD   SD + RTC  MQTT (optional)
       \
        v
   LED / buzzer alert
```

The ESP32 powers the sensors, samples and converts the analog signals, evaluates configured thresholds, updates the local display, and records readings to the SD card with an RTC timestamp. MQTT and OTA are optional integrations. Network TLS and OTA integrity checks remain disabled until the corresponding CA and firmware hash are configured in the local secrets file.
