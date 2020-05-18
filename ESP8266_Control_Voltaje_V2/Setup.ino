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

String WIFI_escanear_redes() {
  int n = WiFi.scanNetworks(); //devuelve el número de redes encontradas
  String mensaje = "";
  Serial.println("escaneo terminado");
  if (n == 0) { //si no encuentra ninguna red
    Serial.println("no se encontraron redes");
    mensaje = "no se encontraron redes";
  }
  else
  {
    Serial.print(n);
    Serial.println(" redes encontradas");
    mensaje = "<option>Seleccione SSID</option>";
    for (int i = 0; i < n; ++i)
    {
      if (WiFi.SSID(i) == ssid) {
        mensaje = (mensaje) + "<option value=\""   + WiFi.SSID(i) + "\" selected=\"selected\">" + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") Ch: " + WiFi.channel(i) + " Enc: " + WiFi.encryptionType(i) + " </option>\r\n";
      } else {
        mensaje = (mensaje) + "<option value=\""   + WiFi.SSID(i) + "\">" + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") Ch: " + WiFi.channel(i) + " Enc: " + WiFi.encryptionType(i) + " </option>\r\n";
      }
      //WiFi.encryptionType 5:WEP 2:WPA/PSK 4:WPA2/PSK 7:open network 8:WPA/WPA2/PSK
      delay(10);
    }
    Serial.println(mensaje);
    return mensaje;
  }
}

void config_rest_server_routing() {

  server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI
  server.on("/config", HTTP_POST, []() {
    handleConfig();
  });
  /*server.on("/config", HTTP_GET, []() {
    server.sendHeader("Location", "/config.html", true);  //Redirect to our html web page
    server.send(302, "text/plane", "");
  });*/
  server.on("/getRedesDisponibles", HTTP_GET, []() {
    server.send(200, "text/plain", WIFI_escanear_redes());
  });
  /*server.on("/getDefaultIP", HTTP_GET, []() {
    server.send(200, "text/plain", IpAddress2String(arduino_ip));
    });*/

  /*server.on("/getDefaultIP", HTTP_GET, []() {
    server.send(200, "application/json", "{\"ip\":\"" + IpAddress2String(arduino_ip) + "\"}");
    });*/

  server.on("/getDefaultIP", HTTP_GET, []() {
    server.send(200, "application/json", IpAddress2String(arduino_ip) );
  });

  server.on("/getDefaultPassword", HTTP_GET, []() {
    server.send(200, "text/plain", pass);
  });
  server.on("/getDefaultGateway", HTTP_GET, []() {
    server.send(200, "text/plain", IpAddress2String(gateway_ip));
  });
  server.on("/reset", HTTP_GET, softReset);
  server.on("/writeAndReset", HTTP_GET, writeAndReset);

  server.on("/getDefaultData", HTTP_GET, []() {
    server.send(200, "application/json", "{\"ip\":\"" + IpAddress2String(arduino_ip) + "\",\"pass\":\"" + pass + "\",\"gateway_ip\":\"" + IpAddress2String(gateway_ip) + "\"}");
  });


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


void softReset() {
  ESP.reset();
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
