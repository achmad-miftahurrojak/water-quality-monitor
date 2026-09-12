#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

#define PIN_TDS 34
#define PIN_PH 35
#define PIN_TURBIDITY 32
#define PIN_BUZZER 25
#define SD_CS 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

const float THRESHOLD_TDS = 500.0;
const float THRESHOLD_PH_LOW = 6.5;
const float THRESHOLD_PH_HIGH = 8.5;
const float THRESHOLD_TURBIDITY = 5.0;

const int NUM_SAMPLES = 10;
float tds_samples[NUM_SAMPLES], ph_samples[NUM_SAMPLES], turb_samples[NUM_SAMPLES];
int sample_index = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Water Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitor Init...");
  
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card Mount Failed");
    lcd.clear();
    lcd.print("SD Init Failed!");
  } else {
    Serial.println("SD Card initialized.");
    File file = SD.open("/datalog.csv", FILE_APPEND);
    if (file) {
      file.println("TDS(ppm),pH,Turbidity(NTU)");
      file.close();
    }
  }
  
  for(int i=0; i<NUM_SAMPLES; i++) {
    tds_samples[i] = 0; ph_samples[i] = 0; turb_samples[i] = 0;
  }
  delay(2000);
  lcd.clear();
}

float getAverage(float* array) {
  float sum = 0;
  for(int i = 0; i < NUM_SAMPLES; i++) sum += array[i];
  return sum / NUM_SAMPLES;
}

void loop() {
  int raw_tds = analogRead(PIN_TDS);
  int raw_ph = analogRead(PIN_PH);
  int raw_turb = analogRead(PIN_TURBIDITY);
  
  float tds = (raw_tds * 3.3 / 4095.0) * 150.0; 
  float ph = 3.5 + (raw_ph * 3.3 / 4095.0) * 1.5; 
  float turbidity = (raw_turb * 3.3 / 4095.0) * 2.5; 

  tds_samples[sample_index] = tds;
  ph_samples[sample_index] = ph;
  turb_samples[sample_index] = turbidity;
  sample_index = (sample_index + 1) % NUM_SAMPLES;

  float avg_tds = getAverage(tds_samples);
  float avg_ph = getAverage(ph_samples);
  float avg_turb = getAverage(turb_samples);

  lcd.setCursor(0, 0);
  lcd.printf("TDS:%d pH:%.1f ", (int)avg_tds, avg_ph);
  lcd.setCursor(0, 1);
  lcd.printf("Turb:%.1f NTU    ", avg_turb);

  bool isUnsafe = (avg_tds > THRESHOLD_TDS) || 
                  (avg_ph < THRESHOLD_PH_LOW) || 
                  (avg_ph > THRESHOLD_PH_HIGH) || 
                  (avg_turb > THRESHOLD_TURBIDITY);

  if (isUnsafe) {
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }

  if (sample_index == 0) {
    File file = SD.open("/datalog.csv", FILE_APPEND);
    if (file) {
      file.printf("%.2f,%.2f,%.2f\n", avg_tds, avg_ph, avg_turb);
      file.close();
      Serial.println("Data logged.");
    }
  }

  delay(1000);
}
