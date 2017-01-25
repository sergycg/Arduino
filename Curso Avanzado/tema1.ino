//Control de envío por puerto serie

switch (estado_hola) {
   case H:
      if (tiempo_trascurrido >= 1000) {
         Serial.println('H');
         estado_hola = O;
         tiempo_transcurrido = 0;
      }
      break;
   case O:
        if (tiempo_transcurrido >= 1000) {
	   Serial.println('O');
	   estado_hola = L;
	   tiempo_transcurrido = 0;
	}
	break;
   case L:
	if (tiempo_transcurrido >= 1000) {
   	   Serial.println('L');
	   estado_hola = A;
	   tiempo_transcurrido = 0;
	}
        break;
   case A: 
	if (tiempo_transcurrido >= 1000) {
	   Serial.println('A');
	   estado_hola = H;
	   tiempo_transcurrido = 0;
	}
        break;
}

//Control del parpadeo del LED

switch (estado_led) {
   case BAJO:
      if (tiempo_trascurrido_led >= 166) {
         digitalWrite(LED, HIGH);
         estado_led = ALTO;
         tiempo_transcurrido_led = 0;
	}
	break;

   case ALTO:
	if (tiempo_transcurrido_led >= 166) {
         digitalWrite(LED, LOW);
         estado_led = BAJO;
         tiempo_transcurrido_led = 0;
	}
	break;
}
		

//Replicamos entrada en salida

if (digitalRead(PULSADOR)){
    digitalWrite(LED2, HIGH);
}
else{
    digitalWrite(LED2, LOW);
}

