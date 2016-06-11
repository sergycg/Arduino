#include <Servo.h> 

Servo servo1;
//Servo servo2;
 
void setup() { 
  servo1.attach(8);
//  servo2.attach(9);
 
} 
 
void loop() { 
  int valor_pot = analogRead(A0);
//  int valor_pot2 = analogRead(A1);
  servo1.write(map(valor_pot, 0,1023, 0, 180));
//  servo2.write(map(valor_pot2, 0,1023, 0, 180));
}
