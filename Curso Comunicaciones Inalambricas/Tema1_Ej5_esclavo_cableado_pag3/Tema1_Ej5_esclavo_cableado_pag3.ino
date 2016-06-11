#define YO 5

void setup() {
  Serial.begin(9600); //Indicamos la velocidad del puerto serie
  pinMode(13, OUTPUT);
}

void loop() {

  byte dato;
  byte accion;
  byte destinatario;

  if (Serial.available() > 0) {
    dato = Serial.read();       //Guardamos el dato enviado en la variable dato
    if (dato > 127) {
      Serial.println("HIGH");
      accion = HIGH;
      destinatario = dato - 128;
    } else {
      Serial.println("LOW");
      accion = LOW;
      destinatario = dato;
    }
    if (destinatario == YO) {
      digitalWrite(13, accion);
    }
    else{
      Serial.println(destinatario);
    }
  }


}
