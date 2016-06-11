#define PIN2 4
#define PIN7 5
#define PIN1 9

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  analogWrite(PIN1, 100);
  
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN7, LOW);
  delay(5000);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN7, HIGH);
  delay(5000);

}
