#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <Arduino.h>
#include "sensors.h"
#include <PubSubClient.h>


void initConnectivity();
bool connectWiFi();
bool connectMQTT();
void disconnectConnectivity();


bool publishTelemetry(SensorData data, float batteryVoltage, uint32_t timestamp);
bool publishAlert(SensorData data, const char* reason, uint32_t timestamp);


PubSubClient& getMqttClient();


void checkForUpdates();

#endif 
