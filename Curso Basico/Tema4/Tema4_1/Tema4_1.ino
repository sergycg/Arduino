byte pin;

void setup() {
  for (pin = 8; pin < 13; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  for (pin = 8; pin < 13; pin++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
  }

  for (pin = 12; pin >= 8; pin--) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
  }

}
