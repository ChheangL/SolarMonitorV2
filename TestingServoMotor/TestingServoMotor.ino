int servopin=4;
int pulse=1500;
void setup() {
  // put your setup code here, to run once:
  pinMode(servopin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
//   put your main code here, to run repeatedly:
  digitalWrite(servopin,HIGH);
  delayMicroseconds(pulse);
  digitalWrite(servopin,LOW);
  delay(20);
}
