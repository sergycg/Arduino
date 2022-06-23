void server_setup()
{
  config_rest_server_routing();
  server.begin();
}

void config_rest_server_routing() {

  server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI

  server.on("/hello", HTTP_GET, []() {
    server.send(200, "text/plain", "hola mundo");
  });

  server.on("/config", HTTP_POST, []() {
    handleConfig();
  });

  server.on("/config", HTTP_GET, []() {
    server.sendHeader("Location", "/config.html", true);  //Redirect to our html web page
    server.send(302, "text/plane", "");
  });

  server.on("/", HTTP_GET, []() {
    server.sendHeader("Location", "/config.html", true);  //Redirect to our html web page
    server.send(302, "text/plane", "");
  });

  server.on("/reestablecer", HTTP_GET, []() {
    server.sendHeader("Location", "/reestablecer.html", true);  //Redirect to our html web page
    server.send(302, "text/plane", "");
  });

  server.on("/getRedesDisponibles", HTTP_GET, []() {
    server.send(200, "text/plain", WIFI_escanear_redes());
  });

  server.on("/reset", HTTP_GET, softReset);

  server.on("/writeAndReset", HTTP_GET, writeAndReset);

  server.on("/getDefaultData", HTTP_GET, []() {
    server.send(200, "application/json", "{\"ip\":\"" + String(configuration.ip) + "\",\"port\":\"" + PORT + "\",\"pass\":\"" + String(configuration.password) + "\",\"gateway_ip\":\"" + String(configuration.gateway) + "\"}");
  });

  server.on("/getADC", handleADC); //Reads ADC function is called from out index.html
}

void handleADC() {

  float sensorValue = analogRead(A0);
  //float voltaje = (5 * sensorValue * (R1 + R2)) / (1024 * R2);
  //voltaje = (5 * sensorValue) / 1024;
  //voltaje = voltaje / (R2/(R1+R2));
  float voltaje = sensorValue * 0.0145;
  String adc = String(voltaje);
  Serial.println(adc);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.send(200, "text/plane", adc);

  /*int a = analogRead(A0);
    a = map(a,0,1023,0,100);
    String adc = String(a);
    Serial.println(adc);
    server.send(200, "text/plane",adc);*/
}

void handleConfig() {

  if (server.hasArg("ssid") && String(server.arg("ssid")) != "" && server.hasArg("Password") && String(server.arg("Password")) != "" && server.hasArg("IP") && String(server.arg("IP")) != "" && server.hasArg("GW") && String(server.arg("GW")) != "") {
    handleConfigSubmit();
  }
  else {//Redisplay the form
    server.sendHeader("Location", "/config.html", true);  //Redirect to our html web page
    server.send(302, "text/plane", "");
  }
}

void handleConfigSubmit() { //dispaly values and write to memmory

  configuration.estado = INICIO;

  String ip = String(server.arg("IP"));
  String ssid = String(server.arg("ssid"));
  String passw = String(server.arg("Password"));
  String gateway = String(server.arg("GW"));
  
  strcpy(configuration.ip, ip.c_str());
  strcpy(configuration.ssid, ssid.c_str());
  strcpy(configuration.password, passw.c_str());
  strcpy(configuration.gateway, gateway.c_str());
  
/*  String ssid_string = String(server.arg("ssid"));
  String pass_string = String(server.arg("Password"));
  ssid_string.toCharArray(ssid, ssid_string.length() + 1);
  pass_string.toCharArray(pass, pass_string.length() + 1);
  arduino_ip.fromString(String(server.arg("IP")));
  gateway_ip.fromString(String(server.arg("GW")));*/

  server.send(200, "application/json", "{\"ip\":\"" + ip + "\",\"ssid\":\"" + ssid + "\",\"gateway_ip\":\"" + gateway + "\"}");

}

/*************** FUNCIONES PARA CARGAR EL ARCHIVO DEL SERVIDOR WEB ***********************************/
/*void handleRoot() {
  server.sendHeader("Location", "/config.html", true);  //Redirect to our html web page
  server.send(302, "text/plane", "");
  }*/

void handleWebRequests() {
  if (loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

bool loadFromSpiffs(String path) {
  String dataType = "text/plain";
  if (path.endsWith("/")) path += "index.htm";

  if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html")) dataType = "text/html";
  else if (path.endsWith(".htm")) dataType = "text/html";
  else if (path.endsWith(".css")) dataType = "text/css";
  else if (path.endsWith(".js")) dataType = "application/javascript";
  else if (path.endsWith(".png")) dataType = "image/png";
  else if (path.endsWith(".gif")) dataType = "image/gif";
  else if (path.endsWith(".jpg")) dataType = "image/jpeg";
  else if (path.endsWith(".ico")) dataType = "image/x-icon";
  else if (path.endsWith(".xml")) dataType = "text/xml";
  else if (path.endsWith(".pdf")) dataType = "application/pdf";
  else if (path.endsWith(".zip")) dataType = "application/zip";
  //  File dataFile = SPIFFS.open(path.c_str(), "r");
  File dataFile = readFile(SPIFFS, path.c_str());
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }

  dataFile.close();
  return true;
}
