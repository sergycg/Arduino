#include <TimerOne.h>

#define PARPADEO_ON   10000000
#define PARPADEO_OFF  500000
#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  Timer1.initialize(PARPADEO_ON); // Inicializamos Temporizador 1 a 1s.
  Timer1.attachInterrupt(parpadea); // Función asociada al desbordamiento. 
  Serial.begin(9600);
}

void parpadea() {
  static boolean estado_led=LOW;
  if (estado_led==LOW){
    estado_led=HIGH;
    digitalWrite(LED, HIGH);
    Timer1.setPeriod(PARPADEO_OFF);
  }else{
    estado_led=LOW;
    digitalWrite(LED, LOW);
    Timer1.setPeriod(PARPADEO_ON);
    
  }
  
}



void loop() {
}
