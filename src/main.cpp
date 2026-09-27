#include <Arduino.h>
#include "alerts.h"
#include "connectivity.h"
#include "power_mgmt.h"
#include "sensors.h"
#include "storage.h"

static const uint32_t SAMPLE_INTERVAL_MS = 30000;
static bool previousAlert = false;
static uint32_t lastSampleAt = 0;

void setup() {
  Serial.begin(115200);
  initPowerMgmt();
  initSensors();
  initAlerts();
  initStorage();
  initConnectivity();
}

void loop() {
  if (millis() - lastSampleAt < SAMPLE_INTERVAL_MS) {
    delay(25);
    return;
  }
  lastSampleAt = millis();

  powerOnSensors();
  SensorData data = readSensors();
  const bool isAlert = checkThresholds(data);
  const float batteryVoltage = readBatteryVoltage();
  const uint32_t timestamp = getCurrentTimestamp();

  updateDisplay(data, isAlert);
  setAlertState(isAlert);

  const bool sentToCloud = publishTelemetry(data, batteryVoltage, timestamp);
  logDataToSD(data, batteryVoltage, isAlert, sentToCloud);

  if (isAlert && !previousAlert) {
    publishAlert(data, data.isError ? "sensor_error" : "threshold_exceeded", timestamp);
  }
  previousAlert = isAlert;

  syncOfflineData();
  powerOffSensors();
}
