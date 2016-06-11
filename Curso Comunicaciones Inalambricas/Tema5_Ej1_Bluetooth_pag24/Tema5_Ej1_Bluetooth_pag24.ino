void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.println("Arrancando...");
}

void loop(){
   char dato;

   if (Serial.available()){
  dato = Serial.read();
  if (dato == '1'){
    digitalWrite(13, HIGH);
    Serial.println("Encendiendo");
  }
  else if (dato == '0'){
    digitalWrite(13, LOW);
    Serial.println("Apagando");
  }
   }
}
