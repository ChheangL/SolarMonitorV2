#include <stdio.h>
HardwareSerial& port = Serial2;
uint8_t i[2] ={0x41,0x8A};

void setup() {
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  init((Stream *)&port);
  delay(1000);
}

void init(Stream* port){
  port->write(i,2);
}
