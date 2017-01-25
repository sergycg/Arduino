#include <TimerOne.h>

#define PARPADEO_OK 	1000000
#define PARPADEO_ERR 	50000
#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  Timer1.initialize(PARPADEO_OK);	// Inicializamos Temporizador 1 a 1s.
  Timer1.attachInterrupt(parpadea);	// Función asociada al desbordamiento. 
  Serial.begin(9600);
}

void parpadea() {
  digitalWrite(LED, !digitalRead(LED));
}

void loop() {
  if (Serial.available() > 0){
    if (Serial.read()=='x') {
      Timer1.setPeriod(PARPADEO_ERR);
    }
    else {
      Timer1.setPeriod(PARPADEO_OK);
    }
  }
}
