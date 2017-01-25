#include <TimerOne.h>

#define PARPADEO_ON   10000000
#define PARPADEO_OFF  500000
#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  Timer1.initialize(PARPADEO_ON); // Inicializamos Temporizador 1 a 1s.
  Timer1.attachInterrupt(enciende); // Función asociada al desbordamiento. 
  Serial.begin(9600);
}

void enciende() {
  digitalWrite(LED, HIGH);
  Timer1.setPeriod(PARPADEO_OFF);
  Timer1.attachInterrupt(apaga);
}

void apaga() {
  digitalWrite(LED, LOW);
  Timer1.setPeriod(PARPADEO_ON);
  Timer1.attachInterrupt(enciende);

}

void loop() {
}
