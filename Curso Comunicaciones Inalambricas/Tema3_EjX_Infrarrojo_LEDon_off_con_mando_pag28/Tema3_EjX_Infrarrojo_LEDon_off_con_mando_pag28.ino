#include <IRremote.h>
#define IR_RX A1

IRrecv receptorIR(IR_RX);
decode_results trama;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  receptorIR.enableIRIn();
}

void loop(){
  if (receptorIR .decode(&trama)) {
    if (trama.decode_type==1){
      Serial.print("Ha llegado: ");
      Serial.println(trama.value,HEX);
      if (trama.value==0xFF30CF){
        digitalWrite(13,HIGH);
      }else if (trama.value==0xFF18E7){
        digitalWrite(13,LOW);
      }
    }
    else{
      Serial.print("Error: ");
      Serial.print(trama.decode_type);
      Serial.print(" ");
      Serial.println(trama.value,HEX);
    }
    receptorIR.resume();
  }
}
