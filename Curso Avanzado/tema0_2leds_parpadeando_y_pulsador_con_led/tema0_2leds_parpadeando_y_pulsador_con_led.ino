#define INTERVALO13 1000
#define INTERVALO12 400
#define LED13 13
#define LED12 12
#define LED7 7
#define PULSADOR 2

unsigned long millisAnterior13 = 0;
unsigned long millisAnterior12 = 0;

void setup() {
  pinMode(LED13, OUTPUT);
  pinMode(LED12, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(PULSADOR, INPUT);
}

void loop() {
  if(millis() - millisAnterior13 >= INTERVALO13) {
    millisAnterior13 = millis();  
    digitalWrite(LED13, !digitalRead(LED13));
  }

  if(millis() - millisAnterior12 >= INTERVALO12) {
    millisAnterior12 = millis();  
    digitalWrite(LED12, !digitalRead(LED12));
  }

/*  if (digitalRead(PULSADOR)==HIGH){
    digitalWrite(LED7, HIGH);
  }else{
    digitalWrite(LED7, LOW);
    
  }*/
  digitalWrite(LED7, digitalRead(PULSADOR));
  
  
}
