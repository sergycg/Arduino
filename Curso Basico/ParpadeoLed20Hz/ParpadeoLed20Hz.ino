#define TIEMPO 25

#define LED 13
#define PULSADOR 2

int lectura_pulsador;

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(PULSADOR, INPUT);
  //Serial.println("Iniciando...");
}

void loop() {

  lectura_pulsador = digitalRead(PULSADOR);

  if (lectura_pulsador == HIGH) {
    Serial.println("1");
    digitalWrite(LED, HIGH);
    delay(TIEMPO);
    digitalWrite(LED, LOW);
    delay(TIEMPO);
  }/*else{
    Serial.println("0");
    digitalWrite(LED, LOW);

  }*/

}
