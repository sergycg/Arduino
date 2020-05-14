void write_to_Memory(String _ssid, String _passw, String _ip, String _gateway) {
  String toWrite = _ssid + ";" + _passw + ";" + _ip + ";" + _gateway + ";";
  write_EEPROM(toWrite, 0);
  EEPROM.commit();
}

//write to memory
void write_EEPROM(String x, int pos) {
  for (int n = pos; n < x.length() + pos; n++) {
    EEPROM.write(n, x[n - pos]);
  }
}

void clear_EEPROM() {
  //  EEPROM.begin(512);
  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  //  EEPROM.end();
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
  ssid = result[1];
  pass = result[2];
  arduino_ip.fromString(result[3]);
  gateway_ip.fromString(result[4]);
}
