#define POTE A1

void setup() {
  pinMode(POTE, INPUT);
  init_7_segmentos();
}

void loop() {
  int lectura_potenciometro;
  for (int i = 15; i >= 0; i--) {
    lectura_potenciometro = analogRead(POTE);
    imprime_7_segmentos(i);
    delay(map(lectura_potenciometro, 0, 1023, 100, 5000));
  }

}


