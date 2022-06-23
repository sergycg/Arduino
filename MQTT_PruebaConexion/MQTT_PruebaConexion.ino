#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
#define LED LED_BUILTIN
 
//Enter your wifi credentials
const char* ssid = "MOVISTAR_2957";  
const char* password =  "61BB34D737589D4D1166";
 
//Enter your mqtt server configurations
const char* mqttServer = "192.168.1.235";    //Enter Your mqttServer address
const int mqttPort = 1883;       //Port number
const char* mqttUser = "mqtt"; //User
const char* mqttPassword = "torped00"; //Password
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  delay(1000);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");
 
}
 
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
 
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  //Conver *byte to String
  }
   Serial.print(message);
  if(message == "#on") {digitalWrite(LED,LOW);}   //LED on  
  if(message == "#off") {digitalWrite(LED,HIGH);} //LED off
 
  Serial.println();
  Serial.println("-----------------------");  
}
 
void loop() {
  client.loop();
}
