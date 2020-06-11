
// ESTADOS
#define FABRICA -1
#define CONFIG 0
#define INICIO 1
#define LUZ_APAGADA 2
#define LUZ_ENCENDIDA 3

#define PIN_LED D4
#define PIN_SIM800L_ON_OFF D1
#define TIMEOUT 10000

#define NUM_PARAMS 5
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include <Hash.h>
#include <FS.h>
//#include "ESPAsyncWebServer.h"
#include <EEPROM.h>
#include <Ticker.h>
#include <SoftwareSerial.h>

SoftwareSerial SIM800L(D8, D7); //Seleccionamos los pines D8 como Rx y D7 como Tx. PIN D7 de arduino con RX de la SIM800L y PIN D8 de arduino con TX de la SIM800L

// Instancia a la clase Ticker
Ticker ticker;

// Pin LED azul
byte pinLed = PIN_LED;

/*
  // Empezamos el temporizador que hará parpadear el LED
  ticker.attach(0.2, parpadeoLed);

    // Eliminamos el temporizador (ponerlo en la parte del codigo donde queramos cerrar el temporizador)
  ticker.detach();

*/

ESP8266WebServer server(32777);
//AsyncWebServer server(80);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "HAKp6xw09rLSbciJShiSduxMshF2b_s8";

// Your WiFi credentials.
// Set password to "" for open networks.
String ssid = "MOVISTAR_2957";
String pass = "61BB34D737589D4D1166";

const char ssid_AP[] = "NodeMCU-ESP8266";    //Definimos la SSDI de nuestro servidor WiFi -nombre de red-
const char password_AP[] = "12345678";       //Definimos la contraseña de nuestro servidor


//byte arduino_mac[] = { 0x5C, 0xCF, 0x7F, 0xD0, 0x0E, 0xF8 };
IPAddress arduino_ip(192, 168, 1, 243);
IPAddress gateway_ip(192, 168, 1, 1);
IPAddress subnet_mask(255, 255, 255, 0);
IPAddress dns_ip(80, 58, 61, 254);

float R1 = 30000;
float R2 = 7500;
int veces = 0;
int estado = FABRICA;

BlynkTimer timer;
WidgetTerminal terminal(V3);

void setup()
{

  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SIM800L_ON_OFF, OUTPUT); // SIM800L PWK pin is conected to D1
  digitalWrite(PIN_SIM800L_ON_OFF, HIGH);

  //estado = INICIO;
  Serial.println();

  ticker.attach(0.05, parpadeoLed); // Empezamos el temporizador que hará parpadear el LED

  // CARGAR CONFIGURACION DE LA EEPROM
  EEPROM.begin(512);

  // CONFIGURACION INICIAL
  //clear_EEPROM();
  //EEPROM.commit();
  //delay(2000);
  //write_to_Memory(String(INICIO), String(ssid), String(pass), IpAddress2String(arduino_ip), IpAddress2String(gateway_ip));
  //delay(2000);

  // OBTENER CONFIGURACION
  read_EEPROM();

  EEPROM.end();
  delay(5000);
  Serial.println();
  //estado = INICIO;

  switch (estado) {
    case CONFIG:
      Serial.println("*******************************************************");
      Serial.println("*                        MODO AP                      *");
      Serial.println("*******************************************************");
      ticker.attach(0.2, parpadeoLed); // Empezamos el temporizador que hará parpadear el LED
      veces = 0;
      WIFI_AP_setup();
      spiffs_setup();
      server_setup();
      delay(3000);
      break;

    case INICIO:
      ticker.attach(0.5, parpadeoLed); // Empezamos el temporizador que hará parpadear el LED
      Serial.println("*******************************************************");
      Serial.println("*                    MODO AP+STA                      *");
      Serial.println("*******************************************************");
      veces = 0;
      WIFI_AP_STA_setup();
      blynk_setup();
      spiffs_setup();
      server_setup();
      delay(3000);
      timer.setInterval(1000L, VCCInput);
      ticker.detach(); // Eliminamos el temporizador (ponerlo en la parte del codigo donde queramos cerrar el temporizador)
      digitalWrite(PIN_LED, LOW); // dejamos el led encendido
      break;

    default:
      /*EEPROM.begin(512);
        clear_EEPROM();
        delay(3000);
        write_EEPROM(String(CONFIG), 0);
        delay(3000);
        EEPROM.end();
        delay(4000);
        softReset();*/
      restaurar_valores_fabrica();
      break;
  }


}


void loop()
{
  switch (estado) {
    case CONFIG:
      server.handleClient();
      break;

    case INICIO:
    case LUZ_APAGADA:
    case LUZ_ENCENDIDA:
      Blynk.run();
      timer.run();
      server.handleClient();
      break;

    default: break;
  }

}
