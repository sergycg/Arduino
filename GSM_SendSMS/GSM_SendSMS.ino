#include <SoftwareSerial.h>
#include <String.h>

#define onModulePin 9


SoftwareSerial mySerial(7, 8);

void setup()
{
  mySerial.begin(19200);
  Serial.begin(19200);
  delay(1000);
  Serial.println("prueba");
  //power_on();
}

void loop()
{


  if (Serial.available())

    switch (Serial.read())
    {
      case 's':
        SendTextMessage();
        break;
      case 'n':
        SendTextMessage2();
        break;

      case 'c':
        DialVoiceCall();
        break;

    }
  if (mySerial.available())
    Serial.write(mySerial.read());
}


void SendTextMessage()
{
  Serial.println("prueba");
  mySerial.print("AT+CMGF=1\r");
  delay(1000);
  mySerial.println("AT+CMGS = \"+34654161878\"");
  delay(1000);
  mySerial.println("Funciona");
  delay(1000);
  mySerial.println((char)26);
  delay(1000);
  mySerial.println();
}

void SendTextMessage2()
{
  int8_t answer;
  //  mySerial.print("AT+CMGF=1\r");
  //  delay(100);
  sendATcommand("AT+CMGF=1\r", "OK", 2000);
  //  mySerial.println("AT+CMGS = \"+34654161878\"");
  //  delay(100);
  answer=sendATcommand("AT+CMGS = \"+34654161878\"", ">", 2000);
  if (answer == 1)
  {
    mySerial.println("South Made");
    //delay(100);
    //mySerial.println((char)26);
    mySerial.print((char)26);
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

void DialVoiceCall()
{
  mySerial.println("ATD+34654161878;");//dial the number
  delay(100);
  mySerial.println();
}

void power_on() {

  uint8_t answer = 0;

  // checks if the module is started
  answer = sendATcommand("AT", "OK", 2000);
  if (answer == 0)
  {
    // power on pulse
    digitalWrite(onModulePin, HIGH);
    delay(3000);
    digitalWrite(onModulePin, LOW);

    // waits for an answer from the module
    while (answer == 0) {   // Send AT every two seconds and wait for the answer
      answer = sendATcommand("AT", "OK", 2000);
    }
  }

}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout) {

  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;

  memset(response, '\0', 100);    // Initialize the string

  delay(100);

  while ( mySerial.available() > 0) mySerial.read();   // Clean the input buffer

  mySerial.println(ATcommand);    // Send the AT command


  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {
    if (mySerial.available() != 0) {
      // if there are data in the UART input buffer, reads it and checks for the asnwer
      response[x] = mySerial.read();
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
