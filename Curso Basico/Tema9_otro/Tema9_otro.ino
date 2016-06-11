void setup() {

  Serial.begin(9600);
  pinMode(A1, INPUT);

}

void loop() {
  byte dato;
  byte brillo;

  int pot=analogRead(A1);
  int conver = map(pot,0,1023,0,5000);
  Serial.print("Voltaje: ");
  Serial.println(conver);
  delay(10);
  
/*  if (Serial.available() > 0) {
    dato = Serial.read();
    Serial.print("Cambiado display a ");
    Serial.println(dato-0x30);
  } 
*/
  // 0x30, 48 o '0' sería lo mismo
}
