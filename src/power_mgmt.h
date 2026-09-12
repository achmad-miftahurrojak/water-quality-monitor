#ifndef POWER_MGMT_H
#define POWER_MGMT_H

#include <Arduino.h>



#define PIN_SENSOR_POWER_MOSFET 12



#define PIN_BATTERY_VOLTAGE 34



#define VBATT_DIVIDER_RATIO 2.0f
#define VBATT_ADC_REF       3.3f
#define VBATT_ADC_MAX       4095.0f

void initPowerMgmt();
void powerOnSensors();
void powerOffSensors();
float readBatteryVoltage();
void goToDeepSleep(uint64_t sleepTimeSeconds);

#endif 
