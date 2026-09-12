#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

// Pin Definitions
#define PIN_TDS 34
#define PIN_PH 35
#define PIN_TURBIDITY 32
#define PIN_BUZZER 25
#define SD_CS 5

// LCD configuration (0x27 is common default)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Thresholds
const float THRESHOLD_TDS = 500.0; // ppm
const float THRESHOLD_PH_LOW = 6.5;
const float THRESHOLD_PH_HIGH = 8.5;
const float THRESHOLD_TURBIDITY = 5.0; // NTU

// Variables for moving average
const int NUM_SAMPLES = 10;
float tds_samples[NUM_SAMPLES], ph_samples[NUM_SAMPLES], turb_samples[NUM_SAMPLES];
int sample_index = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  
  // Init LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Water Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitor Init...");
  
  // Init SD Card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card Mount Failed");
    lcd.clear();
    lcd.print("SD Init Failed!");
  } else {
    Serial.println("SD Card initialized.");
    File file = SD.open("/datalog.csv", FILE_APPEND);
    if (file) {
      // Print CSV header if empty (simplification)
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
  // Read raw analog values (0-4095)
  int raw_tds = analogRead(PIN_TDS);
  int raw_ph = analogRead(PIN_PH);
  int raw_turb = analogRead(PIN_TURBIDITY);
  
  // Convert to actual values (Simplified conversion formulas for demonstration)
  float tds = (raw_tds * 3.3 / 4095.0) * 150.0; 
  float ph = 3.5 + (raw_ph * 3.3 / 4095.0) * 1.5; 
  float turbidity = (raw_turb * 3.3 / 4095.0) * 2.5; 

  // Store in circular buffer
  tds_samples[sample_index] = tds;
  ph_samples[sample_index] = ph;
  turb_samples[sample_index] = turbidity;
  sample_index = (sample_index + 1) % NUM_SAMPLES;

  // Calculate moving average
  float avg_tds = getAverage(tds_samples);
  float avg_ph = getAverage(ph_samples);
  float avg_turb = getAverage(turb_samples);

  // Update Display
  lcd.setCursor(0, 0);
  lcd.printf("TDS:%d pH:%.1f ", (int)avg_tds, avg_ph);
  lcd.setCursor(0, 1);
  lcd.printf("Turb:%.1f NTU    ", avg_turb);

  // Evaluate Thresholds
  bool isUnsafe = (avg_tds > THRESHOLD_TDS) || 
                  (avg_ph < THRESHOLD_PH_LOW) || 
                  (avg_ph > THRESHOLD_PH_HIGH) || 
                  (avg_turb > THRESHOLD_TURBIDITY);

  if (isUnsafe) {
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }

  // Log to SD Card periodically (every 10 cycles = ~10s)
  if (sample_index == 0) {
    File file = SD.open("/datalog.csv", FILE_APPEND);
    if (file) {
      file.printf("%.2f,%.2f,%.2f\n", avg_tds, avg_ph, avg_turb);
      file.close();
      Serial.println("Data logged.");
    }
  }

  delay(1000); // 1Hz sampling
}
