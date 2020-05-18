/*const int numParams = 2;

void readParams(String (& params) [numParams])
  {
  params [0] = "foo";
  params [1] = "bar";
  }

void setup() 
{
  Serial.begin (115200);
  String params [numParams];
  readParams (params);
  for (int i = 0; i < numParams; i++)
    Serial.println (params [i]);
}

void loop() { }*/



/*

  bool serveFile(String path) {
  Serial.println("handleFileRead: " + path);
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, getContentType(path));
    file.close();
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
  //fileContent.replace("{{ip_value}}", arduino_ip.toString());
  //fileContent.replace("{{gw_value}}", gateway_ip.toString());
  //fileContent.replace("{{ssid_value}}", ssid);
  //fileContent.replace("{{password_value}}", pass);
  Serial.println(fileContent);

  file.close();

  //return fileContent;
  }
  bool handleStringFileRead(String path, int code) {
  Serial.println("handleFileRead: " + path);
  if (SPIFFS.exists(path)) {
    server.send(code, getContentType(path), getFileToString(path));
    return true;
  }
  return false;
  }


void config_rest_server_routing() {

  server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI
  server.on("/config", HTTP_POST, []() {
    handleConfig();
  });
  server.on("/config", HTTP_GET, []() {
    server.sendHeader("Location", "/config.html", true);  //Redirect to our html web page
    server.send(302, "text/plane", "");
  });
  server.on("/getRedesDisponibles", HTTP_GET, []() {
    server.send(200, "text/plain", WIFI_escanear_redes());
  });
  server.on("/getDefaultIP", HTTP_GET, []() {
    server.send(200, "text/plain", IpAddress2String(arduino_ip));
  });
  server.on("/getDefaultPassword", HTTP_GET, []() {
    server.send(200, "text/plain", pass);
  });
  server.on("/getDefaultGateway", HTTP_GET, []() {
    server.send(200, "text/plain", IpAddress2String(gateway_ip));
  });
  server.on("/reset", HTTP_GET, softReset);
  server.on("/writeAndReset", HTTP_GET, writeAndReset);


  server.on("/index", HTTP_GET, []() {
    if (!serveFile("/index.html", 200))
      server.send(404, "text/plain", "Archivo no encontrado");
    });


    server.onNotFound([]() {
     server.send(200, "text/html",
                 "Welcome to the ESP8266 REST Web Server");
    });
    //    server.on("/leds", HTTP_GET, get_leds);
    //    server.on("/leds", HTTP_POST, post_put_leds);
    //    server.on("/leds", HTTP_PUT, post_put_leds);
    //  server.on("/prueba", HTTP_GET, prueba);

    server.on("/config", HTTP_GET, []() {
    if (!serveFile("/config.html"))
      server.send(404, "text/plain", "Archivo no encontrado");
    });

}

  
*/
