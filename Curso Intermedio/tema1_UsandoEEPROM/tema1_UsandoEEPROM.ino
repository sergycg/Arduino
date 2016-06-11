#include <EEPROM.h>

#define PULSADOR 2

void setup(){
  Serial.begin(9600);  

  if (digitalRead(PULSADOR)) {
    Serial.println("Reseteando");
    EEPROM.write(10, 0);
  }
}

void loop() {
  byte numero;
  
  numero = EEPROM.read(10);
  Serial.println(numero++);
  EEPROM.write(10, numero);  
  delay(1000);
}
