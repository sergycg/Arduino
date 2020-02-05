void handleConfig() {
  //if (server.hasArg("ssid") && server.hasArg("Password") && server.hasArg("IP") && server.hasArg("GW") ) { //If all form fields contain data call handelSubmit()
  if (server.hasArg("ssid") && String(server.arg("ssid"))!=""){  
    handleConfigSubmit();
  }
  else {//Redisplay the form
    if (!handleStringFileRead("/config.html", 200))
      server.send(404, "text/plain", "Archivo no encontrado");
  }
}
void handleConfigSubmit() { //dispaly values and write to memmory
  String response = "<p>The ssid is ";
  response += server.arg("ssid");
  response += "<br>";
  response += "And the password is ";
  response += server.arg("Password");
  response += "<br>";
  response += "And the IP Address is ";
  response += server.arg("IP");
  response += "</P><BR>";
  response += "<H2><a href=\"/\">go home</a></H2><br>";
  response += "<H2><a href=\"/reset\">Resetear la placa</a></H2><br>";
  server.send(200, "text/html", response);
  //calling function that writes data to memory
  EEPROM.begin(512);
  write_to_Memory(String(server.arg("ssid")), String(server.arg("Password")), String(server.arg("IP")), String(server.arg("GW")));
  delay(2000);
  EEPROM.end();
}
