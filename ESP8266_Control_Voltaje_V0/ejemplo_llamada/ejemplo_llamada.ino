#include <SoftwareSerial.h>

SoftwareSerial SIM800L(D8, D7); //Seleccionamos los pines D8 como Rx y D7 como Tx. PIN D7 de arduino con RX de la SIM800L y PIN D8 de arduino con TX de la SIM800L

// Ademas es necesario que los 5V y GND de arduino esten conectados al pin de 5V y GND de la SIM900


void setup()
{
  // SIM800L PWK pin is conected to D1
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);

  // SIM900.begin(19200);
  // delay(1000);
  Serial.begin(19200);
  Serial.println("setup llamada...");


  // switching on SIM800L by powering down PWK pin for a second
  //digitalWrite(D0, LOW);
  delay(1000);

  //SIM900.begin(19200);
  //SIM900.println("AT");

  SIM800L.begin(19200);
  delay(5000);

  digitalWrite(D1, LOW);
  Serial.println("setup llamada2...");
}

void loop()
{


  delay(20000);
  Serial.println("Realizando llamada...");
  SIM800L.println("ATD912407420;");  //Comando AT para realizar una llamada
  delay(8000);  // Espera 10 segundos mientras realiza la llamada
  SIM800L.println("ATH");  // Cuelga la llamada
  delay(1000);
  Serial.println("Llamada finalizada");

}
