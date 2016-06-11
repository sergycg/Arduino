
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(6, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for (int i=0;i<255;i++){
    analogWrite(6,i);
    delay(15);
  }
  for (int i=254;i>=0;i--){
    analogWrite(6,i);
    delay(15);
  }
}
