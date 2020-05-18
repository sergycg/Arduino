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
