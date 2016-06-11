#include <IRremote.h>
#define IR_RX A1

IRrecv receptorIR(IR_RX);
decode_results trama;

void setup() {
  Serial.begin(9600);
  receptorIR.enableIRIn();
}

void loop(){
  if (receptorIR .decode(&trama)) {
    if (trama.decode_type==1){
      Serial.print("Ha llegado: ");
      Serial.println(trama.value,HEX);
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
