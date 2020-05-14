/******************************* SETUP ******************************/
void WIFI_AP_STA_setup() {

  WiFi.mode(WIFI_STA);

  //  IPAddress arduino_ip2;
  //  arduino_ip2.fromString("192.168.1.241");

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

void WIFI_AP_setup() {

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid_AP, password_AP);      //Red con clave, en el canal 1 y visible
  //WiFi.softAP(ssid, password,3,1);      //Red con clave, en el canal 3 y visible 
  //WiFi.softAP(ssid);                    //Red abierta
  IPAddress ip_AP(192, 168, 1, 242);      //Modifica la dirección IP 
  IPAddress gateway_AP(192, 168, 1, 1);   
  IPAddress subnet_AP(255, 255, 255, 0);
  WiFi.softAPConfig(ip_AP, gateway_AP, subnet_AP);
  Serial.println();
  Serial.print("Direccion IP Access Point - por defecto: ");      
  Serial.println(WiFi.softAPIP()); 
  Serial.print("Direccion MAC Access Point: ");                  
  Serial.println(WiFi.softAPmacAddress()); 


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

  server.on("/config", HTTP_GET, []() {
    if (!handleStringFileRead("/config.html", 200))
      server.send(404, "text/plain", "Archivo no encontrado");
  });
  server.on("/config", HTTP_POST, []() {
    handleConfig();
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
  fileContent.replace("{{ip_value}}", arduino_ip.toString());
  fileContent.replace("{{gw_value}}", gateway_ip.toString());
  fileContent.replace("{{ssid_value}}", ssid);
  fileContent.replace("{{password_value}}", pass);
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
