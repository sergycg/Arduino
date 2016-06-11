#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>
#include <String.h>
#include <Keypad.h>
#include <Wire.h>                 

#define onModulePin 2
#define VOLTAJE_IN A5


SoftwareSerial mySerial(7, 8);

String estado;
String estado_anterior;

//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

LiquidCrystal_I2C lcd(0x27);

const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}
};
byte rowPins[ROWS] = {3,4,5,6}; //Filas
byte colPins[COLS] = {9,10,11}; //Columnas
Keypad keypad = Keypad( makeKeymap(keys), rowPins, 
colPins, ROWS, COLS );
int val=0;//Valor de referencia
int cuadro= 1023;// El numero 1023 dibuja un cuadro en el LCD
String telefono_aux = "";
String telefono = "";

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(onModulePin,OUTPUT);
  pinMode(VOLTAJE_IN, INPUT);

  digitalWrite(onModulePin,HIGH);
  
  estado="INIT";
  estado_anterior=estado;

  mySerial.begin(19200);
  Serial.begin(19200);
  delay(1000);
  Serial.println("Iniciando... estado=" + estado);
  power("off");
  Serial.println("Arrancando módulo GSM...");
  delay(3000);
  power("on");
  Serial.println("Iniciado");
  //leer de la EPROM
}

void loop()
{
  int lectura;
  
  // control del keypad
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
    if(key=='*'){
      modoSetup();
    }
  }
  // leer voltaje de entrada
  lectura = analogRead(VOLTAJE_IN);
  Serial.println(lectura);
  if (lectura>=200){ // Hay luz
    estado_anterior=estado;
    estado="HIGH";
  }else if (lectura<200 && estado=="HIGH"){ // No hay luz
    //SendTextMessage("Se ha ido la luz");
    Serial.println("Se ha ido la luz");
    estado_anterior=estado;
    estado="LOW";
  }
  if (estado_anterior=="LOW" && estado=="HIGH"){ // Se reestabece la luz
    //SendTextMessage("Se ha reestablecido la luz");
    Serial.println("Se ha reestablecido la luz");
  }


  // Control del LED
  if (estado=="HIGH")
    digitalWrite(13,HIGH);
  else digitalWrite(13,LOW);

  // imprimir estado
  Serial.println("Estado=" + estado);
  
  
  
  
  delay(200);

  // imprimir comandos GSM  
  while (mySerial.available())
    Serial.write(mySerial.read());
}


void modoSetup(){
      telefono_aux="";
      Serial.println("Setup *ACEPTAR #BORRAR");
      char key2;
      while(true/*(key2=keypad.getKey())!='*'*/){
        key2=keypad.getKey();
        if (key2=='1' || key2=='2' || key2=='3' || key2=='4' || key2=='5' || key2=='6' || key2=='7' || key2=='8' || key2=='9'){
          if (telefono_aux.length()<9)
            telefono_aux+=key2;
          Serial.println(telefono_aux);
        }else if (key2=='#'){
          if (telefono_aux!=""){
            telefono_aux = telefono_aux.substring(0,telefono_aux.length()-1);
          }
          Serial.println(telefono_aux);
        }else if (key2=='*'){
          if (telefono_aux.length()<9){
            Serial.println("Cancelar? *SI #NO");
            char key3;
            while((key2=keypad.getKey())!='*' && key2!='#'){}
            if (key2=='*'){
              break; 
            }else{
              Serial.println(telefono_aux);
            }
          }else{
             Serial.println("Guardar Telf.? *SI #VOLVER");
            char key3;
            while((key2=keypad.getKey())!='*' && key2!='#'){}
            if (key2=='*'){
              telefono = telefono_aux;
              // guardar en la EPROM
              break; 
            }else{
              Serial.println(telefono_aux);
            }
           
          }
        }
      }
}

void SendTextMessage(String mensaje)
{
//  Serial.println("prueba");
  mySerial.print("AT+CMGF=1\r");
  delay(1000);
  mySerial.println("AT+CMGS = \"+34654161878\"");
  delay(1000);
  mySerial.println(mensaje);
  delay(1000);
  mySerial.println((char)26);
  delay(1000);
  mySerial.println();
}

void SendTextMessage2(String mensaje)
{
  int8_t answer = 0;
  //  mySerial.print("AT+CMGF=1\r");
  //  delay(100);
  sendATcommand("AT+CMGF=1\r", "OK", 2000);
  //  mySerial.println("AT+CMGS = \"+34654161878\"");
  //  delay(100);
  answer=sendATcommand("AT+CMGS = \"+34654161878\"", ">", 2000);
  if (answer != 0)
  {
    mySerial.println(mensaje);
    //delay(100);
    //mySerial.println((char)26);
    mySerial.print((char)26);
    answer = sendATcommand("", "OK", 20000);
    if (answer != 0)
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

void power(String power) {

  uint8_t answer = 0;

  // checks if the module is started
  answer = sendATcommand("AT", "OK", 2000);
  if (power=="on"){
    if (answer == 0)
    {
      // power on pulse
      digitalWrite(onModulePin, LOW);
      delay(3000);
      digitalWrite(onModulePin, HIGH);
  
      // waits for an answer from the module
      while (answer == 0) {   // Send AT every two seconds and wait for the answer
        answer = sendATcommand("AT", "OK", 2000);
      }
    }
  }else{
    if (answer != 0)
    {
      // power on pulse
      digitalWrite(onModulePin, LOW);
      delay(3000);
      digitalWrite(onModulePin, HIGH);
  
      // waits for an answer from the module
      while (answer != 0) {   // Send AT every two seconds and wait for the answer
        answer = sendATcommand("AT", "OK", 2000);
      }
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
