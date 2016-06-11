void setup() {

  Serial.begin(9600);
  pinMode(9, OUTPUT);
  Serial.print("Introduce numeros del 0 al 9: ");

}

void loop() {
  byte dato;
  byte brillo;
  if (Serial.available() > 0) {
    dato = Serial.read();
    brillo = map(dato, 0x30, 0x39, 0, 255);
    analogWrite(9, brillo);
    Serial.print("Cambiado brillo a ");
    Serial.println(dato - 0x30);
  }
}
