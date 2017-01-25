void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {
  float grados = ((analogRead(A0) * (float)1100)/ 1024) / 10;
  Serial.println(grados);
  delay(100);
}
