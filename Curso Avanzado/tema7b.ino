#include <EEPROM.h>

#define EEPROM_ADDRESS 1000
#define TEMPERATURA_BASE 25.0

float toffset = 0.0;

void setup() {
    float f = 0.0;
    
    Serial.begin(9600);
    EEPROM.get(EEPROM_ADDRESS, f);
    if (isnan(f)) {
        toffset = TEMPERATURA_BASE - getTemp();
        EEPROM.put(EEPROM_ADDRESS, toffset);
    }
    else toffset = f;
}

void loop() {
    Serial.print(F("Temperatura: "));
    Serial.print(getTemp());
    Serial.println(F(" C"));
    delay(1000);
}

float get_temp(void) {
    float t;

    // La lectura de temperatura ha de realizarse
    // Con la referencia de 1,1V
    ADMUX = (_BV(REFS1) | _BV(REFS0));
    // Selecciona el canal del sensor de temperatura
    ADMUX |= 0x08;
    // Habilita el ADC
    ADCSRA = _BV(ADEN);
    // Prescaler a 128
    ADCSRA |= (_BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2));
    // Espera un poco a que se estabilicen las tensiones
    delay(20);
    // Inicia la conversión
    ADCSRA |= _BV(ADSC);
    // Espera hasta que la conversión acabe
    while (ADCSRA & _BV(ADSC));
    // Calcula la temperatura en grados Celsius
    t = (0.9424853 * (1.07421875 * (float)ADCW)) - 272.3887 + toffset;
    return t;
}
