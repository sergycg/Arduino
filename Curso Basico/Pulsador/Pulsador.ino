#define LED_INTERNO 13
#define LED_VERDE 12
#define LED_ROJO 3
#define TIEMPO 1000

#define LED 13
#define PULSADOR 2

int lectura_pulsador;

void setup() {

//Establecer direccion de un LED como SALIDA (el led interno de la placa esta cableado internemente por el pin 13)
//pinMode(LED_INTERNO, OUTPUT);
pinMode(LED_VERDE, OUTPUT);
pinMode(LED_ROJO, OUTPUT);

pinMode(LED, OUTPUT);
pinMode(PULSADOR, INPUT);

}

void loop() {

lectura_pulsador = digitalRead(PULSADOR);

if (lectura_pulsador!=HIGH){
  digitalWrite(LED, HIGH);
}else{
  digitalWrite(LED, LOW);
  
}

//Encender
//digitalWrite(LED_INTERNO, HIGH);
//digitalWrite(LED_VERDE, HIGH);
//digitalWrite(LED_ROJO, LOW);

//Esperar
//delay(TIEMPO);

//Apagar
//digitalWrite(LED_INTERNO, LOW);
//digitalWrite(LED_VERDE, LOW);
//digitalWrite(LED_ROJO, HIGH);

//Esperar
//delay(TIEMPO);
}
