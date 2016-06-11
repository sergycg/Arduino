#include <CapacitiveSensor.h>

#define COMUN 2
#define MUESTRAS 10
#define UMBRAL 200 

CapacitiveSensor tecla(COMUN,3);

void setup() { 
  Serial.begin(9600);
  tecla.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop() {    
  if(tecla.capacitiveSensor(MUESTRAS) > UMBRAL)
    Serial.println("Ay!");
}
