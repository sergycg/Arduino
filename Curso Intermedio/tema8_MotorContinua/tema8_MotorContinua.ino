void setup() {
  // initialize digital pin 13 as an output.
  pinMode(6, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(6, HIGH);   
  delay(2000);              
  digitalWrite(6, LOW);    
  delay(2000);              
}
