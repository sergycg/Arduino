#include <TimerOne.h>
#define PARPADEO_OK   1000000
#define PARPADEO_ERR  50000
#define LED 11

void setup() {
  pinMode(LED, OUTPUT);
  Timer1.initialize(100); // Inicializamos Temporizador 1.
  Timer1.attachInterrupt(parpadea); // Función asociada al desbordamiento.
  Serial.begin(9600);
}

void parpadea() {
  static unsigned long contador=0;
  contador++;
  if (contador > PARPADEO_OK / 100){
    contador=0;
    digitalWrite(11, !digitalRead(11));
  }
}

void loop() {
  for (int i = 0; i < 1023; i++) {
    Timer1.pwm(9, i);
    delay(1);
  }
  if (Serial.available() > 0) {
    if (Serial.read() == 'x')
      Timer1.setPeriod(PARPADEO_ERR);
    else
      Timer1.setPeriod(PARPADEO_OK);
  }
} 
