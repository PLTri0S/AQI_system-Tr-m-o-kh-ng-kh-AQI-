//BME280.ino
#include <Wire.h>
#include "BME280.h"
#include "SGP30.h"
#include "Mics-5524.h"
#include "HC8.h"
#include "pms5003.h"
#include "oled.h"

//#define SEALEVELPRESSURE_HPA (1013.25)

unsigned long delayTime = 500;

void setup() {
  Serial.begin(115200);

  initBME(); 
  initSGP();
  initMICS();
  initHC8();
  initPMS();
  setupOLED();
  showBootAnimation();
  delay(1000);

  Serial.print("-- Hoàn tất quá trình khởi động --");
  Serial.println();

}

void loop() { 
  // 1. Read BME280 once and save the values
  int Temp = getBMETemp();
  int Hum = getBMEHum();

  // 2. Read Serial sensors
  updatePMS(); // Pulls data from the PMS buffer once
  int CO2 = get_CO2(); // Pulls data from HC8 buffer
  int CO = get_CO();   // Pulls MICS analog data

  //BME280
  Serial.print("Temperature ");
  Serial.print(Temp);
  Serial.print("°C");

  Serial.print("\t");

  Serial.print("Humidity ");
  Serial.print(Hum);
  Serial.print("%");
  
  Serial.println();

  //SGP30
  applySGPCompensation(Temp, Hum);
  if (readSGP()) {
    Serial.print("TVOC "); Serial.print(get_TVOC()); Serial.print(" ppb"); 

    Serial.print("\t\t");

    Serial.print("eCO2 "); Serial.print(get_eCO2()); Serial.print(" ppm"); 
    Serial.println();
  }
  //MICS-5524
  Serial.print("CO "); Serial.print(CO); Serial.print(" ppm");

  Serial.print("\t\t");

  //HC8
  Serial.print("CO2 "); Serial.print(CO2); Serial.print(" ppm");
  Serial.println();

  //PMS
  Serial.print("PM2.5 "); Serial.print(get_PM25()); Serial.print(" Ug");
  Serial.print("\t\t");
  Serial.print("PM10 "); Serial.print(get_PM10()); Serial.print(" Ug");

  Serial.println();
  Serial.println();

  //Hiển thị trên màn OLED
  updateDisplay(Temp, Hum, get_TVOC(), get_eCO2(), CO2, CO, get_PM25(), get_PM10());

  delay(delayTime);

}
