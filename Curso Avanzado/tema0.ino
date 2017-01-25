#define INTERVALO 500
#define LED 13

unsigned long millisAnterior = 0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  if(millis() - millisAnterior >= INTERVALO) {
    millisAnterior = millis();  
    digitalWrite(LED, !digitalRead(LED));
  }

  //Aquí mi código principal
}
