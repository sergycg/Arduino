#include <IRremote.h>

IRsend emisorIR; //El pin de TX siempre debe ser el 3 (Definido en la librería)

void setup() {
  Serial.begin(9600);
}

void loop(){
  
  emisorIR.sendNEC(0xFF30CF , 32);
  delay(1000);
  emisorIR.sendNEC(0xFF18E7 , 32);
  delay(1000);
}
