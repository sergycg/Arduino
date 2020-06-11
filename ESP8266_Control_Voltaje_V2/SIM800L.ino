
void SIM800L_wakeUp()
{
    // SIM800L PWK pin is conected to PIN_SIM800L_ON_OFF
  digitalWrite(PIN_SIM800L_ON_OFF, HIGH);

  Serial.begin(19200);
  Serial.println("SIM800L OFF -> Encendiendo...");

  delay(1000);

  //SIM900.begin(19200);
  //SIM900.println("AT");

  SIM800L.begin(19200);
  delay(5000);

  digitalWrite(PIN_SIM800L_ON_OFF, LOW);
  Serial.println("SIM800L ON -> Encendiendo...");
  delay(20000);
  Serial.println("SIM800L ON");
}

void SIM800L_powerOn()
{

  uint8_t answer = 0;
  int reintentos = 0;
  
  Serial.println("On Power_on...");

  Serial.begin(19200);
  delay(1000);
  SIM800L.begin(19200);
  delay(5000);

  // checks if the module is started
  answer = sendATcommand("AT\r\n", "OK\r\n", TIMEOUT);
  if (answer == 0)
  {
    // power on pulse
    digitalWrite(PIN_SIM800L_ON_OFF, HIGH);
    delay(3000);
    digitalWrite(PIN_SIM800L_ON_OFF, LOW);

    // waits for an answer from the module
    while (answer == 0 && reintentos < 10)
    {
      // Send AT every two seconds and wait for the answer
      answer = sendATcommand("AT\r\n", "OK\r\n", TIMEOUT);
      Serial.println("Trying connection with module...");
      reintentos++;
    }
  }
}

void SIM800L_call() 
{
  delay(20000);
  Serial.println("Realizando llamada...");
  SIM800L.println("ATD912407420;");  //Comando AT para realizar una llamada
  delay(8000);  // Espera 10 segundos mientras realiza la llamada
  SIM800L.println("ATH");  // Cuelga la llamada
  delay(1000);
  Serial.println("Llamada finalizada");
}

void SIM800L_SendTextMessagePrueba()
{
  Serial.println("prueba");
 // SIM800L.print("AT+CMGF=1\r");
  SIM800L.println("AT+CMGF=1");
  delay(1000);
  //SIM800L.println("AT+CMGS = \"+34654161878\"");
  SIM800L.println("AT+CMGS=\"+34654161878\"");
  delay(1000);
  SIM800L.print("Funciona");
  delay(1000);
  //SIM800L.println((char)26);
  SIM800L.print(char(0x1A));
  delay(1000);
  //SIM800L.println();
}

void SIM800L_SendTextMessage()
{
  int8_t answer;
  //  mySerial.print("AT+CMGF=1\r");
  //  delay(100);
  sendATcommand("AT+CMGF=1", "OK", 2000);
  //  mySerial.println("AT+CMGS = \"+34654161878\"");
  //  delay(100);
  answer = sendATcommand("AT+CMGS=\"+34654161878\"", ">", 2000);
  if (answer == 1)
  {
    SIM800L.println("South Made");
    //delay(100);
    //mySerial.println((char)26);
    SIM800L.print((char)26);
    answer = sendATcommand("", "OK", 20000);
    if (answer == 1)
    {
      Serial.print("Sent ");
    }
    else
    {
      Serial.print("error ");
    }
  } else
  {
    Serial.print("error ");
    Serial.println(answer, DEC);
  }
  //delay(100);
  //mySerial.println();
}


int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout) {

  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;

  memset(response, '\0', 100);    // Initialize the string

  delay(100);

  while ( SIM800L.available() > 0) SIM800L.read();   // Clean the input buffer

  SIM800L.println(ATcommand);    // Send the AT command


  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {
    if (SIM800L.available() != 0) {
      // if there are data in the UART input buffer, reads it and checks for the asnwer
      response[x] = SIM800L.read();
      x++;
      // check if the desired answer  is in the response of the module
      if (strstr(response, expected_answer) != NULL)
      {
        answer = 1;
      }
    }
    // Waits for the asnwer with time out
  } while ((answer == 0) && ((millis() - previous) < timeout));

  return answer;
}
