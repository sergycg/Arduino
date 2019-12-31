/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define INICIO 0
#define LUZ_APAGADA 1
#define LUZ_ENCENDIDA 2

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>  /// OJO: esta con la version 5 para que compile. Hay que subir a la v6 y hacer cambios en el codigo para que funcione
#include <Hash.h>
#include <FS.h>

ESP8266WebServer server(80);

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
  veces = 0;
  estado = INICIO;
  Blynk.virtualWrite(V3, "clr");
  
  // Debug console
  Serial.begin(9600);
  pinMode(D4, OUTPUT);
//  digitalWrite(D4, HIGH);

  terminalPrintln("WIFI Setup...");
  WIFI_setup();
  
  terminalPrint("Blynk Config...");
  //Blynk.begin(auth, ssid, pass);
  Blynk.config(auth);
  Blynk.virtualWrite(V2, " ");
  Blynk.virtualWrite(V4, " ");
  terminalPrintln("OK");

  //Inicia lectura del archivo
  terminalPrint("SPIFFS Config...");
  SPIFFS.begin();
  terminalPrintln("OK");

  terminalPrint("Config Routing...");
  config_rest_server_routing();
  terminalPrintln("OK");

  server.begin();
  Serial.println("Servidor inicializado.");
  terminalPrintln("Servidor inicializado.");

//  checkCallingJsonAPI();

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

  /*    float sensorValue = 0.0;
      float voltaje = 0.0;
      float voltajeTotal = 0.0;

      for (int i=0;i>1000;i++){
        sensorValue = analogRead(A0);
        voltaje = sensorValue*0.0145;
        voltajeTotal += voltaje;
      }
    voltaje = voltajeTotal * 0.001;
  */
  Blynk.virtualWrite(V4, voltaje);
  if (voltaje < 0.75) {
    veces++;
    Blynk.setProperty(V4, "color", "#D3435C"); //ROJO
    if (veces > 5 && estado!=LUZ_APAGADA) {
      terminalPrintln("SE HA IDO LA LUZ...");
      Blynk.email("sergio.camacho@telefonica.net", "Subject: Luz Apagada", "Se ha ido la luz.");
      estado = LUZ_APAGADA;
    }
  } else {
    Blynk.setProperty(V4, "color", "#00FF7F"); //VERDE
    if (veces > 5 &&  estado!=LUZ_ENCENDIDA) {
      terminalPrintln("SE HA RESTAURADO LA LUZ...");
      Blynk.email("sergio.camacho@telefonica.net", "Subject: Luz Encendida", "Se ha restaurado la luz.");
      estado = LUZ_ENCENDIDA;
    }
    veces = 0;
  }

  //Blynk.virtualWrite(V2, analogRead(A0)*0.0145);  // ADC range up to 14.8v
}



//FUNCION PARA IDENTIFICAR EL TIPO DE CONTENIDO DE LOS ARCHIVOS DEL SERVIDOR WEB
String getContentType(String filename) {
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
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

//FUNCION PARA CARGAR EL ARCHIVO DEL SERVIDOR WEB index.html
bool handleFileRead(String path) {
#ifdef DEBUG
  Serial.println("handleFileRead: " + path);
  terminalPrintln("handleFileRead: " + path);
#endif
  //if(path.endsWith("/")) path += "index.html";
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, getContentType(path));
    file.close();
    return true;
  }
  return false;
}


/******************************* SETUP ******************************/
void WIFI_setup(){

  terminalPrintln("WiFi Conectanado.");
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
  terminalPrintln("WiFi conectada.");
  WiFi.printDiag(Serial);
  Serial.println();
  Serial.print("STA dirección IP: ");
  Serial.println(WiFi.localIP());
  
}

void config_rest_server_routing() {

  server.onNotFound([]() {
    //    if(!handleFileRead(server.uri()))
    if (!handleFileRead("/index.html"))
      server.send(404, "text/plain", "Archivo no encontrado");
  });

  server.on("/Welcome", HTTP_GET, []() {
    server.send(200, "text/html",
                "Welcome to the ESP8266 REST Web Server");
  });
  //    server.on("/leds", HTTP_GET, get_leds);
  //    server.on("/leds", HTTP_POST, post_put_leds);
  //    server.on("/leds", HTTP_PUT, post_put_leds);
}
void terminalPrint(String msg){
  terminal.print(msg);
  terminal.flush();  
}

void terminalPrintln(String msg){
  terminal.println(msg);
  terminal.flush();  
}

/******************************* SETUP ******************************/


/*void checkCallingJsonAPI() {
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://jsonplaceholder.typicode.com/users/1");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      //DynamicJsonBuffer jsonBuffer(bufferSize);
      StaticJsonBuffer<1500> jsonBuffer;

      JsonObject& root = jsonBuffer.parseObject(http.getString());

      int id = root["id"];
      const char* name = root["name"];
      const char* username = root["username"];
      const char* email = root["email"];

      Serial.print("Name:");
      Serial.println(name);
      Serial.print("Username:");
      Serial.println(username);
      Serial.print("Email:");
      Serial.println(email);
    }
    http.end(); //Close connection
  }
  //delay(60000);
}*/
