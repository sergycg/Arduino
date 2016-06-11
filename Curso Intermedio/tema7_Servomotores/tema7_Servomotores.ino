#include <Servo.h> 

Servo servo1;
 
void setup() { 
  servo1.attach(8);
} 
 
void loop() { 
  for(int pos = 0; pos < 180; pos += 1) {
    servo1.write(pos);
    delay(15);
  } 
  for(int pos = 180; pos>=1; pos-=1) {                                
    servo1.write(pos);
    delay(15);
  } 
}
