#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>


#define PIN_TDS        35  
#define PIN_TURBIDITY  32  
#define PIN_PH         33  


#define SENSOR_SAMPLE_COUNT 10
#define SENSOR_SAMPLE_DELAY_MS 5


struct SensorData {
    float tds;       
    float turbidity; 
    float ph;        
    bool isError;    
};

void initSensors();
SensorData readSensors();

#endif 
