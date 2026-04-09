#include "HC8.h"

HardwareSerial mySerial(2);
byte response[16];

int last_co2 = 0; // Cache variable to hold the last valid reading

void initHC8() {
  mySerial.begin(9600, SERIAL_8N1, 32, 33);
  Serial.print("Kết nối thành công HC8");
  Serial.println();
}

int get_CO2() {
  if (mySerial.available() > 0) {
    // Check if the next byte in the buffer is the '42' header
    if (mySerial.peek() == 0x42) {
      
      // Wait until the full 16-byte frame arrives
      if (mySerial.available() >= 16) {
        mySerial.readBytes(response, 16);
        
        // Double check both header bytes
        if (response[0] == 0x42 && response[1] == 0x4D) {
          
          // Extract the data from Byte 6 and Byte 7
          int highByte = response[6];
          int lowByte = response[7];
          last_co2 = (highByte * 256) + lowByte; // Update the cache with the fresh data
        }
      }
    } else {
      // If the byte isn't '42', discard it so the buffer doesn't jam
      mySerial.read(); 
    }
  }
  //Quan trong!!!
  return last_co2;
}