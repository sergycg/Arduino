#include <Keyboard.h>
void setup() {
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  char letra;
  if (Serial.available() > 0) {
    letra = Serial.read();
    Keyboard.write(letra-32);
  }  
}
