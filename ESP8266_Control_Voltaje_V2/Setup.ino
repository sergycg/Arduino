/******************************* SETUP ******************************/
void WIFI_STA_setup() {

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
  Serial.print("Inicializando modo AP...");
  Serial.println();
  Serial.print("Direccion IP Access Point - por defecto: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Direccion MAC Access Point: ");
  Serial.println(WiFi.softAPmacAddress());


}

void WIFI_AP_STA_setup() {

  WiFi.mode(WIFI_AP_STA);

  WiFi.softAP(ssid_AP, password_AP);      //Red con clave, en el canal 1 y visible
  IPAddress ip_AP(192, 168, 4, 242);      //Modifica la dirección IP
  IPAddress gateway_AP(192, 168, 4, 1);
  IPAddress subnet_AP(255, 255, 255, 0);
  WiFi.softAPConfig(ip_AP, gateway_AP, subnet_AP);

  Serial.println("********************* MODO AP *************************");
  Serial.print("Inicializando modo AP...");
  Serial.println();
  Serial.print("Direccion IP Access Point - por defecto: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Direccion MAC Access Point: ");
  Serial.println(WiFi.softAPmacAddress());
  Serial.println();
  Serial.println("********************* MODO STA ************************");
  Serial.print("Inicializando modo STA...");
  WiFi.config(arduino_ip, dns_ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  WiFi.setAutoReconnect(true);

  Serial.println();
  Serial.println("WiFi conectada.");
  Serial.println();
  WiFi.printDiag(Serial);
  Serial.println();
  Serial.print("STA dirección IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("*******************************************************");
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
