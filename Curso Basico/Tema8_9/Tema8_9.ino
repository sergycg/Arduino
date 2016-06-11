void setup() {
  pinMode(1, OUTPUT);
}

void loop() {
  int freq;
  freq = map(analogRead(A0), 0, 1023, 50, 8000);
  tone(1, freq);
}
