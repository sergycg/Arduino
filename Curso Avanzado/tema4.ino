#define LED 13
#define PULSADOR 2

volatile int estado = LOW;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PULSADOR, INPUT);
  attachInterrupt(0, cambia, RISING);
}

void loop() {
  digitalWrite(LED, estado=!estado);
  delay(2000);
}

void cambia() {
  digitalWrite(LED, estado=!estado);
}
