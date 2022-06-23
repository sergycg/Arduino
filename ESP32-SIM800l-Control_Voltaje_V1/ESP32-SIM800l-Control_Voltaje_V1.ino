#include <string.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <HTTPClient.h>
//#include <BlynkSimpleEthernet.h>
#include <BlynkSimpleEsp32.h>

//#include <Hash.h>
#include <FS.h>
#include <SPIFFS.h>
#include <EEPROM.h>
#include <Ticker.h>




#define PIN_LED 13
#define TIMEOUT 10000

#define NUM_PARAMS 5
#define BLYNK_PRINT Serial
#define FORMAT_SPIFFS_IF_FAILED true

typedef struct Configurations {
  char ip[50];
  char ssid[50];
  char password[50];
  char gateway[50];
  char subnet[50];
  char dns[50];
  char ssid_ap[50];
  char password_ap[50];
  char ip_ap[50];
  char gateway_ap[50];
  char subnet_ap[50];
  char auth_blynk[50];
  int estado;
} Configuration;

// ESTADOS
/*#define FABRICA -1
#define CONFIG 0
#define INICIO 1
#define LUZ_APAGADA 2
#define LUZ_ENCENDIDA 3*/

const int PORT = 32800;
const int FABRICA = -1;
const int CONFIG = 0;
const int INICIO = 1;
const int LUZ_APAGADA = 2;
const int LUZ_ENCENDIDA = 3;


Ticker ticker; // Instancia a la clase Ticker
byte pinLed = PIN_LED; // Pin LED azul



/*
  // Empezamos el temporizador que hará parpadear el LED
  ticker.attach(0.2, parpadeoLed);

    // Eliminamos el temporizador (ponerlo en la parte del codigo donde queramos cerrar el temporizador)
  ticker.detach();

*/

WebServer server(PORT);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "IWq-1DwXx00qIcofywID_qak5rQqpcIq";

// Your WiFi credentials.
// Set password to "" for open networks.
/*char *ssid = "MOVISTAR_2957";
char *pass = "61BB34D737589D4D1166";

const char ssid_AP[] = "ESP32-SIM800l-CV_v1";    //Definimos la SSDI de nuestro servidor WiFi -nombre de red-
const char password_AP[] = "12345678"; */     //Definimos la contraseña de nuestro servidor

String serverName = "http://pamyser.myqnapcloud.com:38090/api/arduino/voltaje/save";

//byte arduino_mac[] = { 0x5C, 0xCF, 0x7F, 0xD0, 0x0E, 0xF8 };
/*IPAddress arduino_ip(192, 168, 1, 244);
IPAddress gateway_ip(192, 168, 1, 1);
IPAddress subnet_mask(255, 255, 255, 0);
IPAddress dns_ip(80, 58, 61, 254);*/

float R1 = 30000;
float R2 = 7500;
int veces = 0;
int estado = FABRICA;

BlynkTimer timer;
WidgetTerminal terminal(V3);
Configuration configuration;

void setup()
{

  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  Serial.println();
  ticker.attach(0.05, parpadeoLed); // Empezamos el temporizador que hará parpadear el LED
  spiffs_setup();
  delay(500);
  listDir(SPIFFS, "/", 1);
  loadConfig();
  delay(500);
  estado = configuration.estado;
  Serial.print("ESTADO = ");
  Serial.println(estado);
  delay(5000);
  
  /*
    // CARGAR CONFIGURACION DE LA EEPROM
    EEPROM.begin(512);

    // CONFIGURACION INICIAL
    clear_EEPROM();
    EEPROM.commit();
    delay(2000);
    write_to_Memory(String(INICIO), String(ssid), String(pass), IpAddress2String(arduino_ip), IpAddress2String(gateway_ip));
    delay(5000);

    // OBTENER CONFIGURACION
    read_EEPROM();

    EEPROM.end();
    delay(5000);
    Serial.println();
  */



  switch (estado) {
    case CONFIG:
      Serial.println("*******************************************************");
      Serial.println("*                        MODO AP                      *");
      Serial.println("*******************************************************");
      ticker.attach(0.2, parpadeoLed); // Empezamos el temporizador que hará parpadear el LED
      veces = 0;
      WIFI_AP_setup();
      //spiffs_setup();
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
      delay(5000);
      blynk_setup();
      //spiffs_setup();
      server_setup();
      delay(3000);
      //timer.setInterval(1000L, VCCInput);
      //timer.setInterval(300000L, saveSensorValue);
      ticker.detach(); // Eliminamos el temporizador (ponerlo en la parte del codigo donde queramos cerrar el temporizador)
      //listDir(SPIFFS, "/", 1);
      //loadConfig();
      digitalWrite(PIN_LED, HIGH); // dejamos el led encendido
      Serial.println("Ready!");
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
      //restaurar_valores_fabrica();
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
