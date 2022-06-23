/*
void write_to_Memory(String _modo, String _ssid, String _passw, String _ip, String _gateway) {
  String toWrite = _modo + ";" + _ssid + ";" + _passw + ";" + _ip + ";" + _gateway + ";";
  write_EEPROM(toWrite, 0);
  EEPROM.commit();
}

//write to memory
void write_EEPROM(String x, int pos) {
  for (int n = pos; n < x.length() + pos; n++) {
    EEPROM.write(n, x[n - pos]);
  }
}

void writeAndReset() {
  EEPROM.begin(512);
  write_to_Memory(String(INICIO), String(ssid), String(pass), IpAddress2String(arduino_ip), IpAddress2String(gateway_ip));
  delay(2000);
  EEPROM.end();
  delay(1000);
  softReset();
}

void restaurar_valores_fabrica() {
  EEPROM.begin(512);
  clear_EEPROM();
  EEPROM.commit();
  delay(2000);
  EEPROM.end();
  delay(2000);
  softReset();
}

void clear_EEPROM() {
  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
}

void read_EEPROM() {
  String string_Value = "";
  String result[NUM_PARAMS];
  int index = 0;
  Serial.println("Obteniendo configuracion de la EEPROM...");
  Serial.println("");
  for (int n = 0; n < 512 && index < NUM_PARAMS; ++n)
  {
    if (char(EEPROM.read(n)) != ';') {
      string_Value += String(char(EEPROM.read(n)));
    } else {
      Serial.println("CONFIG_" + String(index) + ": " + String(string_Value));
      result[index] = string_Value;
      string_Value = "";
      index++;
      //Serial.println("result " + String(index) + ": " + String(result[index]));
    }

  }
  //Serial.println("Your SSID: " + String(string_Value));
  //  result[0].toCharArray(ssid, result[0].length() + 1);
  //  result[1].toCharArray(pass, result[1].length() + 1);
  estado = result[0].toInt();
  result[1].toCharArray(ssid, result[1].length() + 1);
  result[2].toCharArray(pass, result[2].length() + 1);
  arduino_ip.fromString(result[3]);
  gateway_ip.fromString(result[4]);
}
*/
