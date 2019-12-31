#define BLYNK_PRINT Serial
#define INICIO 0
#define LUZ_APAGADA 1
#define LUZ_ENCENDIDA 2

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include <Hash.h>
#include <FS.h>
//#include "ESPAsyncWebServer.h"

ESP8266WebServer server(80);
//AsyncWebServer server(80);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "HAKp6xw09rLSbciJShiSduxMshF2b_s8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "MOVISTAR_2957";
char pass[] = "61BB34D737589D4D1166";

byte arduino_mac[] = { 0x5C, 0xCF, 0x7F, 0xD0, 0x0E, 0xF8 };
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
  Serial.println("Inicializando...");

  Serial.begin(9600);
  pinMode(D4, OUTPUT);

  veces = 0;
  estado = INICIO;

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
/******************************* SETUP ******************************/
void WIFI_setup() {

  WiFi.mode(WIFI_STA);
  WiFi.config(arduino_ip, dns_ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  WiFi.setAutoReconnect(true);
  Serial.println("WiFi conectada.");
  Serial.println();
  WiFi.printDiag(Serial);
  Serial.println();
  Serial.print("STA dirección IP: ");
  Serial.println(WiFi.localIP());

}

void config_rest_server_routing() {

/*  server.onNotFound([]() {
    if (!handleFileRead("/index.html"))
      server.send(404, "text/plain", "Archivo no encontrado");
  });
*/
  server.onNotFound([]() {
    server.send(200, "text/html",
                "Welcome to the ESP8266 REST Web Server");
  });
  //    server.on("/leds", HTTP_GET, get_leds);
  //    server.on("/leds", HTTP_POST, post_put_leds);
  //    server.on("/leds", HTTP_PUT, post_put_leds);
  server.on("/reset", HTTP_GET, softReset);
  //  server.on("/prueba", HTTP_GET, prueba);

  server.on("/prueba", HTTP_GET, []() {
    if (!handleStringFileRead("/index.html", 200))
      server.send(404, "text/plain", "Archivo no encontrado");
  });

}

void softReset() {
  ESP.reset();
}


//FUNCION PARA CARGAR EL ARCHIVO DEL SERVIDOR WEB
bool handleStringFileRead(String path, int code) {
  Serial.println("handleFileRead: " + path);
  if (SPIFFS.exists(path)) {
    server.send(code, getContentType(path), getFileToString(path));
    return true;
  }
  return false;
}

//FUNCION PARA IDENTIFICAR EL TIPO DE CONTENIDO DE LOS ARCHIVOS DEL SERVIDOR WEB
String getContentType(String filename) {
//  if (server.hasArg("download")) return "application/octet-stream";
//  else 
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

String getFileToString(String path) {
  File file = SPIFFS.open(path, "r");

  Serial.println("- read from file:");
  String fileContent;
  while (file.available()) {
    fileContent += String((char)file.read());
  }
  //fileContent.replace("{{PRUEBA}}", "123456");
  Serial.println(fileContent);

  file.close();
  return fileContent;
}

void terminalPrint(String msg) {
  terminal.print(msg);
  terminal.flush();
}

void terminalPrintln(String msg) {
  terminal.println(msg);
  terminal.flush();
}

void blynk_setup()
{
  Blynk.config(auth);
  Blynk.virtualWrite(V2, " ");
  Blynk.virtualWrite(V4, " ");
  //  Blynk.virtualWrite(V3, "clr");
}

void spiffs_setup()
{
  //Inicia lectura del archivo
  SPIFFS.begin();
}

void server_setup()
{
  config_rest_server_routing();
  server.begin();
}

/******************************* SETUP ******************************/
