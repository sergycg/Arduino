#define LED 8
//#define PULSADOR 2
#define TIEMPO 25
#define TIEMPO_PARPADEO 10000

void setup() {

  pinMode(LED, OUTPUT);
//  pinMode(PULSADOR, INPUT);

  while (millis() <= TIEMPO_PARPADEO) {
    digitalWrite(LED, HIGH);
    delay(TIEMPO);
    digitalWrite(LED, LOW);
    delay(TIEMPO);
  }

}

void loop() {

  //digitalWrite(LED, LOW);
}
