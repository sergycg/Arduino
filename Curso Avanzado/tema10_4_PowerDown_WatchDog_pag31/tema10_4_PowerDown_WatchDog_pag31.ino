#include <EEPROM.h>
#include "LowPower.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    static byte direccion = 100;
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);  
    EEPROM.update(direccion, analogRead(A0)>>2);
    direccion++;

    if (direccion>=159){
      direccion = 100;
      for (int i=100;i<=159;i++){
        Serial.print(EEPROM.read(i));
        Serial.print("");
      }
      Serial.println(".");
      Serial.flush();
    }
}
