void setup() {
  Mouse.begin();
}

void loop() {
  Mouse.move(random(10)-5, random(10)-5, 0);
  delay(10);
}
