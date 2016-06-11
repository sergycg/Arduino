#include <RadioHead.h>
#include <radio_config_Si4460.h>
#include <RHCRC.h>
#include <RHDatagram.h>
#include <RHGenericDriver.h>
#include <RHGenericSPI.h>
#include <RHHardwareSPI.h>
#include <RHMesh.h>
#include <RHNRFSPIDriver.h>
#include <RHReliableDatagram.h>
#include <RHRouter.h>
#include <RHSoftwareSPI.h>
#include <RHSPIDriver.h>
#include <RHTcpProtocol.h>
#include <RH_ASK.h>
#include <RH_CC110.h>
#include <RH_MRF89.h>
#include <RH_NRF24.h>
#include <RH_NRF51.h>
#include <RH_NRF905.h>
#include <RH_RF22.h>
#include <RH_RF24.h>
#include <RH_RF69.h>
#include <RH_RF95.h>
#include <RH_Serial.h>
#include <RH_TCP.h>

RH_ASK fs1000a = RH_ASK(2000, 11, 12, 10, false);

void setup() {
    Serial.begin(9600);
  
    if (fs1000a.init()) Serial.println("Extremo TX. Init OK");
}

void loop() {
  fs1000a.send((uint8_t *)"A", 2);
  fs1000a.waitPacketSent();
  delay(500);

  fs1000a.send((uint8_t *)"B", 2);
  fs1000a.waitPacketSent();
  delay(500);
}
