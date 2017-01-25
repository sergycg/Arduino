#include <TimerOne.h>


void setup() {
  
  Timer1.initialize(1000000); // Inicializamos Temporizador 1 a 1seg.
  Timer1.attachInterrupt(escribe); // Función asociada al desbordamiento. 
  Serial.begin(9600);
}

void escribe() {
  static unsigned int contador_seg = 0;
  contador_seg++;
  if (contador_seg >= 7200){ // cada 2 horas (2 * 3600)
    Serial.println("HOLA");
    contador_seg=0;
  }
}



void loop() {
}
