void blynk_setup()
{
  Blynk.config(configuration.auth_blynk);
   // Blynk.begin(auth, ssid, pass);
   //Blynk.begin(auth);
   Blynk.connect();
  //Blynk.virtualWrite(V2, " ");
  //Blynk.virtualWrite(V4, " ");
  //  Blynk.virtualWrite(V3, "clr");
}
