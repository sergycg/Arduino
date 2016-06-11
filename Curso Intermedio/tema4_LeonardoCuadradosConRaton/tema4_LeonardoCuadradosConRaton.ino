#include <Mouse.h>

void setup() {
  Mouse.begin();
}

void loop() {
    Mouse.move(20, 0, 0);
    delay(15);
    Mouse.move(0, 20, 0);
    delay(15);
    Mouse.move(-20, 0, 0);
    delay(15);
    Mouse.move(0, -20, 0);
    delay(15);
}
