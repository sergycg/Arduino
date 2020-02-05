#define BLYNK_PRINT Serial
#define INICIO 0
#define LUZ_APAGADA 1
#define LUZ_ENCENDIDA 2
#define NUM_PARAMS 4

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include <Hash.h>
#include <FS.h>
//#include "ESPAsyncWebServer.h"
#include <EEPROM.h>

ESP8266WebServer server(80);
//AsyncWebServer server(80);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "HAKp6xw09rLSbciJShiSduxMshF2b_s8";

// Your WiFi credentials.
// Set password to "" for open networks.
String ssid = "MOVISTAR_2957";
String pass = "61BB34D737589D4D1166";

//byte arduino_mac[] = { 0x5C, 0xCF, 0x7F, 0xD0, 0x0E, 0xF8 };
IPAddress arduino_ip(192, 168, 1, 241);
IPAddress gateway_ip(192, 168, 1, 1);
IPAddress subnet_mask(255, 255, 255, 0);
IPAddress dns_ip(80, 58, 61, 254);

float R1 = 30000;
float R2 = 7500;
int veces;
int estado;

BlynkTimer timer;
WidgetTerminal terminal(V3);

void setup()
{
 

  Serial.begin(9600);
  pinMode(D4, OUTPUT);
  veces = 0;
  estado = INICIO;
  Serial.println();
  

  // CARGAR CONFIGURACION DE LA EEPROM
  EEPROM.begin(512);

  // CONFIGURACION INICIAL
//  clear_EEPROM();
//  write_to_Memory(String(ssid), String(pass), IpAddress2String(arduino_ip), IpAddress2String(gateway_ip));
//  delay(2000);

  // OBTENER CONFIGURACION
  read_EEPROM();
  
  EEPROM.end();
  delay(2000);

 
  Serial.println("");
  Serial.print("Inicializando...");
  WIFI_setup();
  blynk_setup();
  spiffs_setup();
  server_setup();

  delay(3000);
  timer.setInterval(1000L, VCCInput);

}


void loop()
{
  Blynk.run();
  timer.run();
  server.handleClient();
}


void VCCInput() {
  Blynk.virtualWrite(V2, ESP.getVcc() * 0.001);

  float sensorValue = analogRead(A0);
  //float voltaje = (5 * sensorValue * (R1 + R2)) / (1024 * R2);
  //voltaje = (5 * sensorValue) / 1024;
  //voltaje = voltaje / (R2/(R1+R2));
  float voltaje = sensorValue * 0.0145;

  Blynk.virtualWrite(V4, voltaje);
  if (voltaje < 0.75) {
    veces++;
    Blynk.setProperty(V4, "color", "#D3435C"); //ROJO
    if (veces > 5 && estado != LUZ_APAGADA) {
      terminalPrintln("SE HA IDO LA LUZ...");
      Blynk.email("sergio.camacho@telefonica.net", "Subject: Luz Apagada", "Se ha ido la luz.");
      estado = LUZ_APAGADA;
    }
  } else {
    Blynk.setProperty(V4, "color", "#00FF7F"); //VERDE
    if (veces > 5 &&  estado != LUZ_ENCENDIDA) {
      terminalPrintln("SE HA RESTAURADO LA LUZ...");
      Blynk.email("sergio.camacho@telefonica.net", "Subject: Luz Encendida", "Se ha restaurado la luz.");
      estado = LUZ_ENCENDIDA;
    }
    veces = 0;
  }

}

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ;
}

//FUNCION PARA CARGAR EL ARCHIVO DEL SERVIDOR WEB index.html
/*bool handleFileRead(String path) {
  //#ifdef DEBUG
  Serial.println("handleFileRead: " + path);
  //#endif
  //if(path.endsWith("/")) path += "index.html";
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");

    size_t sent = server.streamFile(file, getContentType(path));
    file.close();
    return true;
  }
  return false;
  }


  String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while (file.available()) {
    fileContent += String((char)file.read());
  }
  Serial.println(fileContent);
  return fileContent;
  }
*/
