
void VCCInput() {
  float voltaje = readVoltajeSensor();

  Blynk.virtualWrite(V2, ESP.getVcc() * 0.001);
  Blynk.virtualWrite(V4, voltaje);
  if (voltaje < 0.75) {
    veces++;
    Blynk.setProperty(V4, "color", "#D3435C"); //ROJO
    if (veces > 1 && estado != LUZ_APAGADA) {
      estado = LUZ_APAGADA;
      terminalPrintln("SE HA IDO LA LUZ...");
      Blynk.email("sergio.camacho@telefonica.net", "Subject: Luz Apagada", "Se ha ido la luz.");
      sendHttpSensorValue(voltaje);
    }
  } else {
    Blynk.setProperty(V4, "color", "#00FF7F"); //VERDE
    if (veces > 1 &&  estado != LUZ_ENCENDIDA) {
      estado = LUZ_ENCENDIDA;
      terminalPrintln("SE HA RESTAURADO LA LUZ...");
      Blynk.email("sergio.camacho@telefonica.net", "Subject: Luz Encendida", "Se ha restaurado la luz.");
      sendHttpSensorValue(voltaje);
    }
    veces = 0;
  }

}

void saveSensorValue() {
  float voltaje = readVoltajeSensor();
  sendHttpSensorValue(voltaje);
}


void sendHttpSensorValue(float voltaje) {
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(serverName);

  // Specify content-type header
  // If you need an HTTP request with a content type: application/x-www-form-urlencoded, use the following:
  //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  // Data to send with HTTP POST
  //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";
  // Send HTTP POST request
  //int httpResponseCode = http.POST(httpRequestData);

  // If you need an HTTP request with a content type: application/json, use the following:
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST("{\"voltaje\":\"" + String(voltaje) + "\"}");

  // If you need an HTTP request with a content type: text/plain
  //http.addHeader("Content-Type", "text/plain");
  //int httpResponseCode = http.POST("Hello, World!");

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  // Free resources
  http.end();
}

float readVoltajeSensor() {

  float sensorValue = analogRead(A0);
  //float voltaje = (5 * sensorValue * (R1 + R2)) / (1024 * R2);
  //voltaje = (5 * sensorValue) / 1024;
  //voltaje = voltaje / (R2/(R1+R2));
  float voltaje = sensorValue * 0.0145;
  return voltaje;
}


String IpAddress2String(const IPAddress & ipAddress)
{
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3])  ;
}

void parpadeoLed() {
  // Cambiar de estado el LED
  byte estado = digitalRead(pinLed);
  digitalWrite(pinLed, !estado);
}

void terminalPrint(String msg) {
  terminal.print(msg);
  terminal.flush();
}

void terminalPrintln(String msg) {
  terminal.println(msg);
  terminal.flush();
}

void softReset() {
  ESP.reset();
}






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

  //FUNCION PARA CARGAR EL ARCHIVO DEL SERVIDOR WEB index.html
  bool handleFileRead(String path) {
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
