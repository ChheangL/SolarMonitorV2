void setup() {
  Serial.begin(115200);
}

void loop() {
  float voltage = 0;
  int sample =150;
  float sum = 0;
  for (int i=0 ; i<=sample; i++){
    sum = sum + analogRead(A0);
  }
  voltage = sum/sample;
  voltage = voltage *3.36/4095.0;
  float current = (voltage - 1.62)*1/0.0503; //need to determind this
  Serial.println("Current"+String((int(round(current*10)))/10.0));
    Serial.println("Current"+String(current));

  Serial.println("voltageRead: "+String(voltage));
  delay(100);
}
