void loadConfig() {
  Serial.println("loadConfig: ");
  File configFile =  SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("- failed to open config file");
    return;
  }

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, configFile);
  //serializeJson(doc, Serial);
  strcpy(configuration.ip, doc["ip"]);
  strcpy(configuration.ssid, doc["ssid"]);
  strcpy(configuration.password, doc["password"]);
  strcpy(configuration.gateway, doc["gateway"]);
  strcpy(configuration.subnet, doc["subnet"]);
  strcpy(configuration.dns, doc["dns"]);
  strcpy(configuration.ssid_ap, doc["ssid_ap"]);
  strcpy(configuration.password_ap, doc["password_ap"]);
  strcpy(configuration.ip_ap, doc["ip_ap"]);
  strcpy(configuration.gateway_ap, doc["gateway_ap"]);
  strcpy(configuration.subnet_ap, doc["subnet_ap"]);
  strcpy(configuration.auth_blynk, doc["auth_blynk"]);
  configuration.estado = doc["estado"];
  configFile.close();

  Serial.println(configuration.ip);
  Serial.println(configuration.ssid);
  Serial.println(configuration.password);
  Serial.println(configuration.gateway);
  Serial.println(configuration.subnet);
  Serial.println(configuration.dns);
  Serial.println(configuration.ssid_ap);
  Serial.println(configuration.password_ap);
  Serial.println(configuration.ip_ap);
  Serial.println(configuration.gateway_ap);
  Serial.println(configuration.subnet_ap);
  Serial.println(configuration.auth_blynk);
  Serial.println(configuration.estado);
  Serial.println("");
  Serial.println(" - config.json load - OK.");
}


void saveConfig() {
  Serial.println("saveConfig: ");
//  File configFile =  SPIFFS.open("/config.json", "r");
//  if (!configFile) {
//    Serial.println("- failed to open config file for writing");
//    return;
//  }
  DynamicJsonDocument doc(2048);
//  deserializeJson(doc, configFile);
  //serializeJson(doc, Serial);
//  configFile.close();
  //
  doc["ip"] = configuration.ip;
  doc["ssid"] = configuration.ssid;
  doc["password"] = configuration.password;
  doc["gateway"] = configuration.gateway;
  doc["subnet"] = configuration.subnet;
  doc["dns"] = configuration.dns;
  doc["ssid_ap"] = configuration.ssid_ap;
  doc["password_ap"] = configuration.password_ap;
  doc["ip_ap"] = configuration.ip_ap;
  doc["gateway_ap"] = configuration.gateway_ap;
  doc["subnet_ap"] = configuration.subnet_ap;
  doc["auth_blynk"] = configuration.auth_blynk;
  doc["estado"] = configuration.estado;
  //
  File configFile =  SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("- failed to open config file");
    return;
  }
  serializeJson(doc, configFile);
  serializeJson(doc, Serial);
  configFile.close();
  Serial.println("");
  Serial.println(" - config.json saved - OK.");
}

/*void ConfigFile_Save_Variable(String VarName, String VarValue) {
  Serial.print("ConfigFile_Save_Variable: ");
  Serial.print(VarName); Serial.print("="); Serial.print(VarValue);

  File configFile =  SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("- failed to open config file for writing");
    return;
  }

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, configFile);
  serializeJson(doc, Serial);
  configFile.close();
  //
  doc[VarName] = VarValue;
  //
  configFile = SPIFFS.open("/config.json", "w");
  serializeJson(doc, configFile);
  serializeJson(doc, Serial);
  configFile.close();
  Serial.println("");
  Serial.println(" - config.json saved - OK.");
}*/
/***************************************************************************************************/
