void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  int pot0;
  int dimmer_led;

  pot0 = analogRead(A1);
  dimmer_led = map(pot0, 0, 1023, 0, 255);
  analogWrite(3, dimmer_led);
}
