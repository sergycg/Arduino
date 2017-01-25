#include <avr/wdt.h>

void setup() {
  wdt_disable();        	//Importantísimo: Deshabilitamos el WDT lo primero
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  delay(5000);          	//Este delay nos permite reprogramar en cualquier caso
  digitalWrite(11, LOW);
  wdt_enable(WDTO_4S);	//Habilitamos el WDT configurado a 4 segundos

}

void loop() {

  if (digitalRead(2)==HIGH){
    wdt_reset();		//Si no ejecutamos esta orden, Arduino se reiniciará
  }

}
