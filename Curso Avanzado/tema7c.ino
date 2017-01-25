#include <avr/sleep.h>

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.print(F("Valor analogico leido: "));
    Serial.println(analogRead_reduccion_ruido(A0));
    delay(500);
}

int analogRead_reduccion_ruido(unsigned char pin) {
    unsigned char oldTIMSK0 = 0;

    if (pin >= 14) pin -= 14;	// Para el pin de entrada indicado
    if (!(ADCSRA & _BV(ADSC))) { // Si no está el ADC en conversión
        ADCSRA = _BV(ADEN);	// Habilita el ADC
        ADCSRA |= (_BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2));	// Prescaler a 128
        ADCSRA |= _BV(ADIE); // Habilitar la interrupción al finalizar conversión 
        ADMUX = (0x1 << 6) | (pin & 0x07);//Selecciona el canal 
        set_sleep_mode(SLEEP_MODE_ADC); // Configura el modo de bajo consumo
        oldTIMSK0 = TIMSK0;// Copia el estado de las interrupciones de timer0 antes de
				// deshabilitarlas . Esto causará inexactitud en millis()
        TIMSK0 = 0;		//Deshabilita interrupciones en timer0 mientras no se haya 					//completado la conversión
        do {
            sleep_enable(); 	// Habilita la capacidad de suspensión
            sei();			//Habilitar interrupciones para poder despertar
            // En el modo SLEEP_MODE_ADC la conversión inicia en cuanto la CPU suspende
            sleep_cpu();		//Entrar en modo SLEEP.
            // Si esta línea se ejecuta es que se ha despertado
            sleep_disable();//Acabamos de despertar, así que deshabilitamos el sleep
            cli();	        //La comprobación de conversión finalizada ha de hacerse 					 //con las interrupciones deshabilitadas
        } while (ADCSRA & _BV(ADSC));
        ADCSRA &= ~(_BV(ADIE));	// Deshabilita la interrupción por ADC
        sei();// Habilita las interrupciones globales
        TIMSK0 = oldTIMSK0;  // Restaura las interrupciones del timer0
        return(ADCW);// Devuelve el resultado de la conversión
    }
    else return -1;
}

ISR(ADC_vect) {} //Esta función debe existir para que la interrupción se ejecute
