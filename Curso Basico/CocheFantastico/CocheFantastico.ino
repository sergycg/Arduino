#define TIEMPO 300

#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
//#define PULSADOR 2

int lectura_pulsador;

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  //pinMode(PULSADOR, INPUT);
  //Serial.println("Iniciando...");
}

void loop() {

//  lectura_pulsador = digitalRead(PULSADOR);

  //    Serial.println("1");
  digitalWrite(LED1, HIGH);
  delay(TIEMPO);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(TIEMPO);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(TIEMPO);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  delay(TIEMPO);
  digitalWrite(LED4, LOW);
  digitalWrite(LED3, HIGH);
  delay(TIEMPO);
  digitalWrite(LED3, LOW);
  digitalWrite(LED2, HIGH);
  delay(TIEMPO);
  digitalWrite(LED2, LOW);


}
