#define LED 9

void setup() {
    pinMode(LED, OUTPUT);

    TCCR1A = 0xA2;    // Modo 14, TOP = IRC1
    TCCR1B = 0x19;    // Sin prescaler
    ICR1 = 0xffff;    // Resolución representada por bits a '1'
}

void loop() {
    static unsigned int brillo = 0;
    static char incremento = 1;

    analogWriteT1(LED, brillo);
    brillo += incremento;
    if (brillo <= 0 || brillo >= ICR1) incremento = -incremento;
    delayMicroseconds(10);
}

void analogWriteT1(byte pin, unsigned int val) {
    switch (pin) {
        case  9: OCR1A = val;
        break;
        case 10: OCR1B = val;
        break;
    }
}
