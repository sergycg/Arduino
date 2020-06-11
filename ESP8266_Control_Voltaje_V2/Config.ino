void config_rest_server_routing() {

  server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI

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
    server.send(200, "application/json", "{\"ip\":\"" + IpAddress2String(arduino_ip) + "\",\"pass\":\"" + pass + "\",\"gateway_ip\":\"" + IpAddress2String(gateway_ip) + "\"}");
  });

  server.on("/getADC", handleADC); //Reads ADC function is called from out index.html

  /*server.on("/getDefaultIP", HTTP_GET, []() {
     server.send(200, "text/plain", IpAddress2String(arduino_ip));
     });*/

  /*server.on("/getDefaultIP", HTTP_GET, []() {
    server.send(200, "application/json", "{\"ip\":\"" + IpAddress2String(arduino_ip) + "\"}");
    });

    server.on("/getDefaultIP", HTTP_GET, []() {
    server.send(200, "application/json", IpAddress2String(arduino_ip) );
    });

    server.on("/getDefaultPassword", HTTP_GET, []() {
    server.send(200, "text/plain", pass);
    });
    server.on("/getDefaultGateway", HTTP_GET, []() {
    server.send(200, "text/plain", IpAddress2String(gateway_ip));
    });*/
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

  estado = INICIO;
  ssid = String(server.arg("ssid"));
  pass = String(server.arg("Password"));
  arduino_ip.fromString(String(server.arg("IP")));
  gateway_ip.fromString(String(server.arg("GW")));

  /*String response = "<p>The ssid is ";
    response += server.arg("ssid");
    response += "<br>";
    response += "And the password is ";
    response += server.arg("Password");
    response += "<br>";
    response += "And the IP Address is ";
    response += server.arg("IP");
    response += "</P><BR>";
    response += "<p>Reinicie la placa para aplicar los cambios.</p><BR>";
    response += "<H3><a href=\"/config.html\">Volver</a></H3><br>";
    response += "<H3><a href=\"/writeAndReset\">Reiniciar la placa</a></H3><br>";
    server.send(200, "text/html", response);*/

  server.send(200, "application/json", "{\"ip\":\"" + IpAddress2String(arduino_ip) + "\",\"ssid\":\"" + ssid + "\",\"gateway_ip\":\"" + IpAddress2String(gateway_ip) + "\"}");

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
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }

  dataFile.close();
  return true;
}

/***************************************************************************************************/
