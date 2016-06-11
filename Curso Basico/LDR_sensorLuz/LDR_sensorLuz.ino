void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int pot0;
  int dimmer_led;

  pot0 = analogRead(A0);
  Serial.println(pot0);
}
