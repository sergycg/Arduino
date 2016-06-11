#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Pines donde está conectado el LCD

void setup() {
  lcd.begin(16, 2); //16 columnas y 2 filas
  lcd.setCursor(0,0);
  lcd.print("Hola mundo!");
  lcd.setCursor(0,1);
  lcd.print("millis: ");
}

void loop() {
  lcd.setCursor(8, 1);
  lcd.print(millis());
}
