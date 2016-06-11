#include <Servo.h>

Servo servo1;

// dos botones, cuando se pulsa uno el motor gira hacia un sentido, y cuando se pulsael otro boton gira hacia el otro sentido

int posicion;

void setup() {
  servo1.attach(8);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  posicion = 90;
}

void loop() {

  if (digitalRead(2) == HIGH) {
    if (posicion < 180)
      posicion++;
  }
  if (digitalRead(3) == HIGH) {
    if (posicion > 0)
      posicion--;

  }
  servo1.write(posicion);
  delay(15);
}
