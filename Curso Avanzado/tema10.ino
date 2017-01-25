#include "LowPower.h"

#define PULSADOR 2
#define LED 11

void despierta(){
}

void setup() {
  Serial.begin(9600);
  pinMode(PULSADOR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  attachInterrupt(0, despierta, CHANGE);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  detachInterrupt(0);
  digitalWrite(LED, HIGH);
  Serial.println("Hola");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.flush();
}
