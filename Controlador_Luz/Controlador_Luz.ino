#include <EEPROM.h>

#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>
#include <String.h>
#include <Keypad.h>
#include <Wire.h>                 

#define onModulePin 2
#define VOLTAJE_IN A0
#define POS_EEPROM 10


SoftwareSerial mySerial(7, 8);

String estado;
String estado_anterior;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//LiquidCrystal_I2C lcd(0x27);

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
char telefono_envio_SMS[9];

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(onModulePin,OUTPUT);
  pinMode(VOLTAJE_IN, INPUT);

  digitalWrite(onModulePin,HIGH);

  lcd.begin(16,2);//Arranca LCD
  
  estado="INIT";
  estado_anterior=estado;

  mySerial.begin(19200);
  Serial.begin(19200);
  delay(1000);
  Serial.println("Iniciando... estado=" + estado);
  //pinta en lcd
  lcd.setCursor(2,0);             
  lcd.print("Iniciando...");
  power("off"); //apaga GSM
  Serial.println("Arrancando módulo GSM...");
  //pinta en lcd
  lcd.clear();
  lcd.setCursor(3,0);             
  lcd.print("Arrancando");
  lcd.setCursor(3,1);             
  lcd.print("modulo GSM");

  delay(3000);
  power("on"); //Inicia GSM
  Serial.println("Iniciado");

  //pinta en lcd
  lcd.clear();
  lcd.setCursor(4,0);             
  lcd.print("Iniciado");
  lcd.setCursor(0,1);             
  lcd.print("Setup pulsar '*'");

  //leer de la EPROM
  EEPROM.get(POS_EEPROM,telefono_envio_SMS);
  
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
    }else if(key=='#'){
      //pinta en lcd
      lcd.clear();
      lcd.setCursor(4,0);             
      lcd.print("Iniciado");
      lcd.setCursor(0,1);             
      lcd.print(telefonoCharToString(telefono_envio_SMS));
      Serial.println(telefonoCharToString(telefono_envio_SMS));
      delay(3000);
      //pinta en lcd
      lcd.clear();
      lcd.setCursor(4,0);             
      lcd.print("Iniciado");
      lcd.setCursor(0,1);             
      lcd.print("Setup pulsar '*'");
    }
  }

  // leer voltaje de entrada
  lectura = analogRead(VOLTAJE_IN);
  Serial.println(lectura);
  if (lectura>=200){ // Hay luz
    estado_anterior=estado;
    estado="HIGH";
  }else if (lectura<200 && estado=="HIGH"){ // No hay luz
    SendTextMessage("Se ha ido la luz");
    //Serial.println("Se ha ido la luz");
    estado_anterior=estado;
    estado="LOW";
  }
  if (estado_anterior=="LOW" && estado=="HIGH"){ // Se reestabece la luz
    SendTextMessage("Se ha reestablecido la luz");
    //Serial.println("Se ha reestablecido la luz");
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
      // pinta en lcd
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("*ACEPTAR #BORRAR");
      
      char key2;
      while(true/*(key2=keypad.getKey())!='*'*/){
        key2=keypad.getKey();
        if (key2=='1' || key2=='2' || key2=='3' || key2=='4' || key2=='5' || key2=='6' || key2=='7' || key2=='8' || key2=='9'){
          if (telefono_aux.length()<9)
            telefono_aux+=key2;
          Serial.println(telefono_aux);

          // pinta en lcd
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("*ACEPTAR #BORRAR");
          lcd.setCursor(0,1);
          lcd.print(telefono_aux);
          
        }else if (key2=='#'){
          if (telefono_aux!=""){
            telefono_aux = telefono_aux.substring(0,telefono_aux.length()-1);
          }
          Serial.println(telefono_aux);

          // pinta en lcd
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("*ACEPTAR #BORRAR");
          lcd.setCursor(0,1);
          lcd.print(telefono_aux);

        }else if (key2=='*'){
          if (telefono_aux.length()<9){
            Serial.println("Cancelar? *SI #NO");

            // pinta en lcd
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Cancel? *SI #NO");
            lcd.setCursor(0,1);
            lcd.print(telefono_aux);

            char key3;
            while((key2=keypad.getKey())!='*' && key2!='#'){}
            if (key2=='*'){
              break; 
            }else{
              Serial.println(telefono_aux);

              // pinta en lcd
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("*ACEPTAR #BORRAR");
              lcd.setCursor(0,1);
              lcd.print(telefono_aux);

            }
          }else{
              Serial.println("Guardar Telf.? *SI #VOLVER");

              // pinta en lcd
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Guardar" + telefono_aux + "?");
              lcd.setCursor(0,1);
              lcd.print("*SI #VOLVER");
            
            char key3;
            while((key2=keypad.getKey())!='*' && key2!='#'){}
            if (key2=='*'){
              telefono = telefono_aux;
              for (int i=0;i<telefono.length();i++){
                telefono_envio_SMS[i]=telefono[i];
                //Serial.print(telefono_envio_SMS[i]);
                //delay(1000);
              }
              Serial.println(telefono_envio_SMS);
              delay(1000);
              // guardar en la EPROM
              EEPROM.put(POS_EEPROM, telefono_envio_SMS);
              break; 
            }else{
              Serial.println(telefono_aux);

              // pinta en lcd
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("*ACEPTAR #BORRAR");
              lcd.setCursor(0,1);
              lcd.print(telefono_aux);
            }
           
          }
        }
      }

  //pinta en lcd
  lcd.clear();
  lcd.setCursor(4,0);             
  lcd.print("Iniciado");
  lcd.setCursor(0,1);             
  lcd.print("Setup pulsar '*'");

}

String telefonoCharToString(char telefono[]){
  String telefonoString = "";
  for (byte i=0;i<9;i++){
    telefonoString += telefono[i];
  }
  return telefonoString;
}

void SendTextMessage(String mensaje)
{


  char* c1 = "AT+CMGS = \"+34";
  char* c2 = "123456789";
  char* c4 = "\"";
  for (int i=0;i<9;i++){
    c2[i]=telefono_envio_SMS[i];
  }
  char* c3;
  c3 = (char*)malloc(strlen(c1)+strlen(c2)+strlen(c4)); 
  strcpy(c3, c1); 
  strcat(c3, c2); 
  strcat(c3, c4); 



//  Serial.println("prueba");
  mySerial.print("AT+CMGF=1\r");
  delay(1000);
  //mySerial.println("AT+CMGS = \"+34654161878\"");
  mySerial.println(c3);
  delay(1000);
  mySerial.println(mensaje);
  delay(1000);
  mySerial.println((char)26);
  delay(1000);
  mySerial.println();
}

void SendTextMessage2(String mensaje)
{

  char* c1 = "AT+CMGS = \"+34";
  char* c2 = "123456789";
  char* c4 = "\"";
  for (int i=0;i<9;i++){
    c2[i]=telefono_envio_SMS[i];
  }
  char* c3;
  c3 = (char*)malloc(strlen(c1)+strlen(c2)+strlen(c4)); 
  strcpy(c3, c1); 
  strcat(c3, c2); 
  strcat(c3, c4); 

  
  int8_t answer = 0;
  //  mySerial.print("AT+CMGF=1\r");
  //  delay(100);
  sendATcommand("AT+CMGF=1\r", "OK", 2000);
  //  mySerial.println("AT+CMGS = \"+34654161878\"");
  //  delay(100);
//  answer=sendATcommand("AT+CMGS = \"+34654161878\"", ">", 2000);
  answer=sendATcommand(c3, ">", 2000);
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
  mySerial.println("ATD+34"+telefonoCharToString(telefono_envio_SMS)+";");//dial the number
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
