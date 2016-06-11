#include <Stepper.h>
//Grados por paso: 5.625° = 64 pasos por vuelta
#define PASOS 64 
#define REDUCTORA 32

Stepper stepper28byj48(PASOS, 8, 10, 9, 11);

void setup() {
  //stepper28byj48.setSpeed(400); //RPM
}

void loop() {

  int valor_pot = analogRead(A0);
  
   stepper28byj48.setSpeed(map(valor_pot,0,1023,0,200)); //RPM
 
  stepper28byj48.step(1);
  //delay(1000);
  //stepper28byj48.step((-1)*(50));
}
