#include<SPI.h>

void setup() {
//Serial.begin(115200);
//pinMode(3,OUTPUT);
//SPI.beginTransaction(SPISettings(14000000,MSBFIRST,SPI_MODE0));
SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV8);    

SPI.transfer(0x1);
}
//int t=255/2;
void loop() {
  //delay(1000);
  //SPI.transfer(0b00100101);

//  // put your main code here, to run repeatedly:
//  //if(t>=255)t=0;
//  if(Serial.available()>0){
//    t = Serial.readString().toInt();
//  }
//  digitalWrite(3,1);
//  delayMicroseconds(t);
//  digitalWrite(3,0);
//  delayMicroseconds(t);
//  //t+=1;
//  Serial.println(t);
  
}
