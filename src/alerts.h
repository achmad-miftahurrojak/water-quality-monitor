#ifndef ALERTS_H
#define ALERTS_H

#include <Arduino.h>
#include "sensors.h"


#define PIN_BUZZER     25
#define PIN_LED_RED    26
#define PIN_LED_YELLOW 27
#define PIN_LED_GREEN  14


#define THRESHOLD_TDS_HIGH         500.0f  
#define THRESHOLD_TURBIDITY_HIGH    25.0f  
#define THRESHOLD_PH_LOW             6.5f  
#define THRESHOLD_PH_HIGH            8.5f  

void initAlerts();
bool checkThresholds(SensorData data);
void setAlertState(bool isAlert);
void updateDisplay(SensorData data, bool isAlert);
void silenceAlerts();   

#endif 
