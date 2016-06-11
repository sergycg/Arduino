#define POTE A0

void setup() {
  Serial.begin(9600);
  pinMode(POTE, INPUT);
  init_7_segmentos();
}

void loop() {
  int lectura;
  lectura = analogRead(POTE);
  if (lectura<(1023/3)){
    imprime_7_segmentos(0);
  }else if(lectura>((1023/3)*2)){
    imprime_7_segmentos(2);
  }else{
    imprime_7_segmentos(1);
  }
  Serial.println(lectura);
//  delay(10);
}
