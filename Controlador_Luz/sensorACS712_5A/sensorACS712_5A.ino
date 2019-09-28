float Sensibilidad=0.185; //sensibilidad en Voltios/Amperio para sensor de 5A
int on_off = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  
  float voltajeSensor =get_voltage(20000);//obtenemos voltaje del sensor(10000 muestras) 
  float corriente = (voltajeSensor-2.5)/Sensibilidad; //Ecuación  para obtener la corriente 
  Serial.print("Voltaje del sensor: ");
  Serial.println(voltajeSensor - 2.5 ,3);    
  Serial.print("Intensidad del sensor: ");
  Serial.println(corriente ,3);    
  if (corriente > 0.075)
  {
    //on_off = 1;
    digitalWrite(13, HIGH);
  }else{
    //on_off = 0;
    digitalWrite(13, LOW);
    
  }
}


float get_voltage(int n_muestras)
{
  float voltage=0;
  
  for(int i=0;i<n_muestras;i++)
  {
    voltage =voltage+analogRead(A0) * (5.0 / 1023.0);    
  }
  voltage=voltage/n_muestras;
  return(voltage);
}
