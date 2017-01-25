#define led 11

void setup() {
    pinMode(led, OUTPUT);
}

void loop() {
    static byte brillo = 0;
    static byte incremento = 1;

    analogWrite(led, brillo);
    brillo += incremento;
    if ( brillo <= 0 || brillo >= 255) {
	incremento = -incremento;
    }
    delay(10);
}
