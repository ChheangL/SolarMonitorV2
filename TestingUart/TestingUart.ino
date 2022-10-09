
void setup() {
   // put your setup code here, to run once:
  //Serial2 Tx 17 , Rx 16
  Serial2.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial2.print(char(0x41)); //print out A using HEX 0011 0001
  delay(1000);
}
