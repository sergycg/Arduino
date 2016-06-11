
void setup() {
  for (int i = 10; i < 14; i++)
    pinMode(i, INPUT);
  init_7_segmentos();
}

void loop() {
  //  int botones_pulsados;
  //  botones_pulsados=cuenta_botones();
  //  imprime_7_segmentos(botones_pulsados);
  for (int i = 15; i >= 0; i--) {
    imprime_7_segmentos(i);
    delay(500);
  }

}

int cuenta_botones() {
  int contador = 0;

  for (int i = 10; i < 14; i++)
    if (digitalRead(i) == HIGH) contador++;
  return contador;
}


