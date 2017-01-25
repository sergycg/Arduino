#include "LowPower.h"

#define LED 11

void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    //Entra en modo de bajo consumo y a los 4 segundos es despertado por el WDT
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);  

    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
}
