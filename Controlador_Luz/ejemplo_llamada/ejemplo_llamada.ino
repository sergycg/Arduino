#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); //Seleccionamos los pines 7 como Rx y 8 como Tx. PIN 7 de arduino con 7 de la SIM900 y PIN 8 de arduino con 8 de la SIM900

// Ademas es necesario que los 5V y GND de arduino esten conectados al pin de 5V y GND de la SIM900


void setup()
{
 SIM900.begin(19200);
 Serial.begin(19200);
 delay(1000);
 
}

void loop()
{

 
delay(10000);
Serial.println("Realizando llamada...");
      SIM900.println("ATD606368230;");  //Comando AT para realizar una llamada
      delay(20000);  // Espera 20 segundos mientras realiza la llamada
      SIM900.println("ATH");  // Cuelga la llamada
      delay(1000);
      Serial.println("Llamada finalizada");
 
}
