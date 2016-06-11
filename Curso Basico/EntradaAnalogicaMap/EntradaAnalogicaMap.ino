#define POTE A0

void setup() {
  Serial.begin(9600);
  pinMode(POTE, INPUT);
  init_7_segmentos();
}

void loop() {
  int lectura;
  lectura = analogRead(POTE);
  imprime_7_segmentos(map(lectura, 0, 1023, 0, 15));
  Serial.println(lectura);
//  delay(10);
}
