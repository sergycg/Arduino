void setup() {
    bitSet(ADCSRA, ADPS2);
    bitClear(ADCSRA, ADPS1);
    bitClear(ADCSRA, ADPS0);
}

void loop() {
	if (analogRead(A0) > 100){
		digitalWrite(13, HIGH);
	}
	else{
		digitalWrite(13, LOW);
	}
}
