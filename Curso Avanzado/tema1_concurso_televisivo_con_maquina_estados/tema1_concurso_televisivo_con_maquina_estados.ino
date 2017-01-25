
typedef enum{
  INICIO = 1,
  ESPERA_RESPUESTA = 2,
  RESPUESTA_VERDE = 3,
  RESPUESTA_ROJO = 4,
  FIN_RONDA = 5,
  FIN = 6
} estado_concurso_t;

#define PULSADOR_PRESENTADOR 2
#define PULSADOR_VERDE 3
#define PULSADOR_ROJO 4
#define LED_ROJO 12
#define LED_VERDE 13


void setup() {
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(PULSADOR_PRESENTADOR, INPUT);
  pinMode(PULSADOR_VERDE, INPUT);
  pinMode(PULSADOR_ROJO, INPUT);
}

void loop() {
  static estado_concurso_t estado = INICIO;
  switch (estado) {
   case INICIO:
      if (digitalRead(PULSADOR_PRESENTADOR)==HIGH){
        estado = ESPERA_RESPUESTA;
      }
      break;
   case ESPERA_RESPUESTA:
      if (digitalRead(PULSADOR_VERDE)==HIGH){
        estado = RESPUESTA_VERDE;
      }
      if (digitalRead(PULSADOR_ROJO)==HIGH){
        estado = RESPUESTA_ROJO;
      }
      break;
   case RESPUESTA_VERDE:
        digitalWrite(LED_VERDE, HIGH);
        estado = FIN_RONDA;
        break;
   case RESPUESTA_ROJO:
        digitalWrite(LED_ROJO, HIGH);
        estado = FIN_RONDA;
        break;
   case FIN_RONDA:
      if (digitalRead(PULSADOR_PRESENTADOR)==HIGH){
        digitalWrite(LED_ROJO, LOW);
        digitalWrite(LED_VERDE, LOW);
        estado = FIN;
      }
      break;
   case FIN:
      if (digitalRead(PULSADOR_PRESENTADOR)==LOW){
        estado = INICIO;
      }
      break;


}

}
