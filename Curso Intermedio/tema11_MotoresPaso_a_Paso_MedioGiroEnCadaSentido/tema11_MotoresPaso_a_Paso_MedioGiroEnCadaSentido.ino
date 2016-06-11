#include <Stepper.h>
//Grados por paso: 5.625° = 64 pasos por vuelta
#define PASOS 64 
#define REDUCTORA 32

Stepper stepper28byj48(PASOS, 8, 10, 9, 11);

void setup() {
  stepper28byj48.setSpeed(200); //RPM
}

void loop() {
  stepper28byj48.step(PASOS*REDUCTORA/2);
  delay(1000);
  stepper28byj48.step((-1)*(PASOS*REDUCTORA/2));
}
