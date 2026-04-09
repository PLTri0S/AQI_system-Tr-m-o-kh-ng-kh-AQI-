#include "Mics-5524.h"
#include "DFRobot_MICS.h"

#define ADC_PIN  15
#define POWER_PIN 2

DFRobot_MICS_ADC mics(ADC_PIN, POWER_PIN);

void initMICS() {
  while (!mics.begin()) {
    Serial.println("Kiểm tra kết nối MICS!");
    return;
  }
  Serial.print("Kết nối thành công MICS");
  Serial.println();

}

int get_CO() {
  return int(mics.getGasData(CO));
}