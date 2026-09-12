#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include "sensors.h"

#define PIN_SD_CS 5 

void initStorage();
void logDataToSD(SensorData data, float batteryVoltage, bool isAlert, bool sentToCloud);
uint32_t getCurrentTimestamp();


void syncOfflineData();

#endif 
