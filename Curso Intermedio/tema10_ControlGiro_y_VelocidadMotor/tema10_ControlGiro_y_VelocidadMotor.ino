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
  int valor_pot = analogRead(A0);
  if (valor_pot <= 502) {
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN7, LOW);
    analogWrite(PIN1, map (valor_pot,502,0,0,255));


  } else if (valor_pot >= 522) {
    digitalWrite(PIN2, LOW);
    digitalWrite(PIN7, HIGH);
    analogWrite(PIN1, map (valor_pot-522,0,502,0,255));

  }else{
    digitalWrite(PIN2, LOW);
    digitalWrite(PIN7, LOW); 
    // ó  analogWrite(PIN1,0);
  }


}
