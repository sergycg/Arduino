#include <RH_ASK.h>
#include <SPI.h>
#define MAX_MSG_LEN 59

RH_ASK receptor = RH_ASK(2000, 11, 12, 10, false);

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  if (receptor.init()) Serial.println("Extremo RX. Init OK");
}

void loop() {
  uint8_t msg[MAX_MSG_LEN];
  uint8_t len = sizeof(msg);

  if (receptor.recv(msg, &len)) {
    char accion = msg[0];
    if (accion=='I'){
      digitalWrite(13,HIGH);
    }else if (accion=='J'){
      digitalWrite(13,LOW);
    }
  }
} 
