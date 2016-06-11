void setup() {

  Serial.begin(9600);
  pinMode(9, OUTPUT);
  init_7_segmentos();
  Serial.print("Introduce numeros del 0 al 9: ");

}

void loop() {
  byte dato;
  byte brillo;
  if (Serial.available() > 0) {
    dato = Serial.read();
    imprime_7_segmentos(dato-0x30);
    Serial.print("Cambiado display a ");
    Serial.println(dato-0x30);
  } 

  // 0x30, 48 o '0' sería lo mismo
}
