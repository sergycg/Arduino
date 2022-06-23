/******************************* SETUP ******************************/
void WIFI_STA_setup() {

  IPAddress ip, gateway, subnet, dns;
  ip.fromString(configuration.ip);
  gateway.fromString(configuration.gateway);
  subnet.fromString(configuration.subnet);
  dns.fromString(configuration.dns);

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, dns, gateway, subnet);
  WiFi.begin(configuration.ssid, configuration.password);
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

  IPAddress ip_AP, gateway_AP, subnet_AP;
  ip_AP.fromString(configuration.ip_ap);
  gateway_AP.fromString(configuration.gateway_ap);
  subnet_AP.fromString(configuration.subnet_ap);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(configuration.ssid_ap, configuration.password_ap);      //Red con clave, en el canal 1 y visible
  //WiFi.softAP(ssid, password,3,1);      //Red con clave, en el canal 3 y visible
  //WiFi.softAP(ssid);                    //Red abierta
  /*IPAddress ip_AP(192, 168, 1, 244);      //Modifica la dirección IP
    IPAddress gateway_AP(192, 168, 1, 1);
    IPAddress subnet_AP(255, 255, 255, 0);*/
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

  IPAddress ip, gateway, subnet, dns;
  ip.fromString(configuration.ip);
  gateway.fromString(configuration.gateway);
  subnet.fromString(configuration.subnet);
  dns.fromString(configuration.dns);

  IPAddress ip_AP, gateway_AP, subnet_AP;
  ip_AP.fromString(configuration.ip_ap);
  gateway_AP.fromString(configuration.gateway_ap);
  subnet_AP.fromString(configuration.subnet_ap);

  WiFi.mode(WIFI_AP_STA);

  WiFi.softAP(configuration.ssid_ap, configuration.password_ap);      //Red con clave, en el canal 1 y visible
  /*  IPAddress ip_AP(192, 168, 4, 244);      //Modifica la dirección IP
    IPAddress gateway_AP(192, 168, 4, 1);
    IPAddress subnet_AP(255, 255, 255, 0);*/
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

  /*IPAddress arduino_ip(192, 168, 1, 108);
    IPAddress gateway_ip(192, 168, 1, 1);
    IPAddress subnet_mask(255, 255, 255, 0);
    IPAddress dns_ip(80, 58, 61, 254);
    char *ssid = "MOVISTAR_2957";
    char *pass = "61BB34D737589D4D1166";

    WiFi.config(arduino_ip, gateway_ip, subnet_mask, dns_ip);
    WiFi.begin(ssid, pass);*/

  WiFi.config(ip, gateway, subnet, dns);
  WiFi.begin(configuration.ssid, configuration.password);

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
      if (WiFi.SSID(i) == configuration.ssid) {
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







/******************************* SETUP ******************************/
