#include <EEPROM.h>

#define PULSADOR 2

byte numero;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT);
  numero = EEPROM.read(10);

}

void loop() {


  if (digitalRead(PULSADOR) == HIGH) {

    numero++;
    
    if (numero > 4) {
      numero = 0;
      for (int i = 0; i < 4; i++) {
        digitalWrite(i + 3, LOW);
      }
    }
    EEPROM.update(10, numero);
    delay(300);
  }
  for (int i = 0; i < numero; i++) {
    digitalWrite(i + 3, HIGH);
  }

}
