void setup() {
  pinMode(3, OUTPUT);
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
