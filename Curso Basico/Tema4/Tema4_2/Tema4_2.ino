#define PULSADOR 2

byte pin;



void setup() {
  pinMode(PULSADOR, INPUT);
  for (pin = 8; pin < 13; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  if (digitalRead(PULSADOR) == HIGH) {
    for (pin = 8; pin < 13; pin++) {
      digitalWrite(pin, HIGH);
      delay(100);
      digitalWrite(pin, LOW);
    }
  } else {
    for (pin = 12; pin >= 8; pin--) {
      digitalWrite(pin, HIGH);
      delay(100);
      digitalWrite(pin, LOW);
    }
  }
}
