#define POT A0
void setup() {
  Serial.begin(115200);
}
float potValue= 0;
void loop() {
  potValue = map(analogRead(POT),660,0,180,9);
  
  Serial.println("POT read : "+String(potValue));
  delay(200);
}
