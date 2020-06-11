#include <SoftwareSerial.h>
#define TIMEOUT 10000

SoftwareSerial SIM800L(D8, D7); //Seleccionamos los pines D8 como Rx y D7 como Tx. PIN D7 de arduino con RX de la SIM800L y PIN D8 de arduino con TX de la SIM800L

// Ademas es necesario que los 5V y GND de arduino esten conectados al pin de 5V y GND de la SIM900


void setup()
{
  // SIM800L PWK pin is conected to D1
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);

  // SIM900.begin(19200);
  // delay(1000);
  Serial.begin(19200);
  Serial.println("setup llamada...");


  // switching on SIM800L by powering down PWK pin for a second
  //digitalWrite(D0, LOW);
  delay(1000);

  //SIM900.begin(19200);
  //SIM900.println("AT");

  SIM800L.begin(19200);
  delay(5000);
  power_on();
  Serial.println("Conectado!!");
  /*digitalWrite(D1, LOW);
    Serial.println("setup llamada2...");
    delay(20000);
    Serial.println("enviando SMS...");
    int8_t answer1;
    answer1 = sendATcommand("AT", "OK", 2000);
    if (answer1 == 1)
    {
    Serial.print("Sent AT ");
    }
    else
    {
    Serial.print("error ");
    }*/
  //SendTextMessage2();
  //call();
}

void loop()
{

  if (SIM800L.available())
    Serial.write(SIM800L.read());
  if (Serial.available())
    SIM800L.write(Serial.read());
}


void power_on()
{

  uint8_t answer = 0;

  Serial.println("On Power_on...");

  // checks if the module is started
  answer = sendATcommand("AT\r\n", "OK\r\n", TIMEOUT);
  if (answer == 0)
  {
    // power on pulse
    digitalWrite(D1, HIGH);
    delay(3000);
    digitalWrite(D1, LOW);

    // waits for an answer from the module
    while (answer == 0)
    {
      // Send AT every two seconds and wait for the answer
      answer = sendATcommand("AT\r\n", "OK\r\n", TIMEOUT);
      Serial.println("Trying connection with module...");
    }
  }
}
void call()
{
  delay(20000);
  Serial.println("Realizando llamada...");
  SIM800L.println("ATD912407420;");  //Comando AT para realizar una llamada
  delay(8000);  // Espera 10 segundos mientras realiza la llamada
  SIM800L.println("ATH");  // Cuelga la llamada
  delay(1000);
  Serial.println("Llamada finalizada");
}

void SendTextMessage()
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

void SendTextMessage2()
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
