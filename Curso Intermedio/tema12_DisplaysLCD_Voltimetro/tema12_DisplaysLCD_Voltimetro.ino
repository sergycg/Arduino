#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Pines donde está conectado el LCD

void setup() {
  pinMode(A0,INPUT);
  
  lcd.begin(16, 2); //16 columnas y 2 filas
  lcd.setCursor(0,0);
  lcd.print("Hola mundo!");
  lcd.setCursor(0,1);
  lcd.print("Tension: ");
}

void loop() {
  int valor_pot = analogRead(A0);
  //analogWrite(PIN1, map (valor_pot,502,0,0,255));
  lcd.setCursor(10, 1);
  lcd.print("    ");
  lcd.setCursor(10, 1);
  float valor = (float)map (valor_pot,0,1023,0,5000)/1000;
  lcd.print(valor);
  delay(30);
}
