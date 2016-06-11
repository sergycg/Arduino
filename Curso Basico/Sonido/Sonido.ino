#define TIEMPO 100

#define DO 262
#define RE 294
#define MI 330
#define FA 349
#define SOL 392
#define LA 440
#define SI 494

void setup() {
  pinMode(3, OUTPUT);
  pinMode(1,OUTPUT);
  tone(1,DO,TIEMPO);
  delay(TIEMPO);
  tone(1,RE,TIEMPO);
  delay(TIEMPO);
  tone(1,MI,TIEMPO);
  delay(TIEMPO);
  tone(1,FA,TIEMPO);
  delay(TIEMPO);
  tone(1,SOL,TIEMPO);
  delay(TIEMPO);
  tone(1,LA,TIEMPO);
  delay(TIEMPO);
  tone(1,SI,TIEMPO);
  delay(TIEMPO);
}

void loop() {
  int pot0;
  int dimmer_led;

  for (int i = 0; i < 255; i++) {
  //for (int i = 0; i < 1024; i++) {
    //dimmer_led = map(i, 0, 1023, 0, 255);
    //analogWrite(3, dimmer_led);
    analogWrite(3, i);
    delay(10);

  }

  for (int i = 255; i >= 0; i--) {
  //for (int i = 1023; i >= 0; i--) {
    //dimmer_led = map(i, 0, 1023, 0, 255);
    //analogWrite(3, dimmer_led);
    analogWrite(3, i);
    delay(10);

  }

}
