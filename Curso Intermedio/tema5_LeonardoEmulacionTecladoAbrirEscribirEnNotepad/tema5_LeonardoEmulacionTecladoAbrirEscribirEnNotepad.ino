#include <Keyboard.h>
void setup() {
  Keyboard.begin();
}

void loop() {
  if (digitalRead(2)==HIGH){
    Keyboard.end();
  }
  delay(1000);
  Keyboard.press(KEY_LEFT_GUI); //tecla windows
  delay(1000);
  Keyboard.press('r'); // tecla R
  delay(1000);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("notepad");
  delay(1000);
  Keyboard.print("\n");
  delay(1000);
  Keyboard.println("Hola");
  while(1){}
}
