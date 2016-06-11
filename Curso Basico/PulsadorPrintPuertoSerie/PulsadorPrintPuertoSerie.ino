#define LED_INTERNO 13
#define LED_VERDE 12
#define LED_ROJO 3
#define TIEMPO 1000

#define LED 13
#define PULSADOR1 2
#define PULSADOR2 3

int lectura_pulsador1;
int lectura_pulsador2;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED, OUTPUT);
  pinMode(PULSADOR1, INPUT);
  pinMode(PULSADOR2, INPUT);
  //Serial.println("Iniciando...");
}

void loop() {

  lectura_pulsador1 = digitalRead(PULSADOR1);
  lectura_pulsador2 = digitalRead(PULSADOR2);
  
  if (lectura_pulsador1==HIGH || lectura_pulsador2==HIGH){
    Serial.println("1");
    digitalWrite(LED, HIGH);
  }else{
    Serial.println("0");
    digitalWrite(LED, LOW);
    
  }

}
