void setup(){
  Serial.begin(9600); //Indicamos la velocidad del puerto serie 
}

void loop() {

  Serial.print('E');
  delay(200);
  Serial.print('A');
  delay(200);
  
}
