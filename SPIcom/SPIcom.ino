
/*
  Digital Pot Control

  This example controls an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.

 The AD5206 is SPI-compatible,and to command it, you send two bytes,
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).

 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)

 created 10 Aug 2010
 by Tom Igoe

 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005

*/


// inslude the SPI library:
#include <SPI.h>

#define CONV_AVG_MASK 0x7000
#define CONV_AVG_1x 0x0
#define CONV_AVG_2x 0x1000
#define CONV_AVG_4x 0x2000
#define CONV_AVG_8x 0x3000
#define CONV_AVG_16x 0x4000
#define CONV_AVG_32x 0x5000

#define MAG_TEMPCO_MASK 0x300
#define MAG_TEMPCO_0pd 0x0
#define MAG_TEMPCO_0R12pd 0x100
#define MAG_TEMPCO_0R2pd 0x300

#define OPERATING_MODE_MASK 0x70
#define OPERATING_MODE_ConfigurationMode 0x0
#define OPERATING_MODE_StandbyMode 0x10
#define OPERATING_MODE_activeMeasureMode 0x20
#define OPERATING_MODE_ActiveTriggerMode 0x30
#define OPERATING_MODE_WakeupAndSleepMode 0x40
#define OPERATING_MODE_SleepMode 0x50
#define OPERATING_MODE_DeepsleepMode 0x60

#define T_CH_EN_TempChannelDisabled 0x0
#define T_CH_EN_TempChannelEnabled 0x8

#define T_RATE_sameAsOtherSensors 0x0
#define T_RATE_oncePerConversionSet 0x4

#define T_HLT_EN_tempLimitCheckOff 0x0
#define T_HLT_EN_tempLimitCheckOn 0x2

#define TEMP_COMP_EN_TempCompensationDisenabled 0x0
#define TEMP_COMP_EN_TempCompensationEnabled 0x1



// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
uint16_t address = 0x0F0F;

uint8_t rcvBuffer[4];
uint8_t sendBuffer[4]= {0x0F, 0x00, 0x04, 0x00};;


void inital(uint16_t slaveSelectPin)
{
  slaveSelectPin = slaveSelectPin;
  pinMode(slaveSelectPin, OUTPUT);
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));
  SPI.begin();
  sndSPI();
}

void sndSPI()
{
  digitalWrite(slaveSelectPin, LOW);
  // send CSI data
  for (int i = 0; i < 4; i++)
  {
    rcvBuffer[i] = SPI.transfer(sendBuffer[i]);
  }
  // CS pin goes hi
  digitalWrite(slaveSelectPin, HIGH);
}



void writeConfig(uint8_t regis, uint16_t data){
  sendBuffer[0] = 0x00<<7 | regis;
  sendBuffer[1] = data>>8;
  sendBuffer[2] = data;
  sendBuffer[3] = 0x00;
  sndSPI();
}

void readRegis(uint8_t regis){
  sendBuffer[0] = 0x01<<7 | regis;
  sendBuffer[1] = 0x00;
  sendBuffer[2] = 0x00;
  sendBuffer[3] = 0x00;
  sndSPI();
}

void readX(){
  readRegis(0x09);
  printWBuffer();
  printRBuffer();
}
void readY(){
  readRegis(0x0A);
  printWBuffer();
  printRBuffer();
}
void readZ(){
  readRegis(0x0B);
  printWBuffer();
  printRBuffer();
}

void ZeroSend(){
  sendBuffer[0] = 0x00;
  sendBuffer[1] = 0x00;
  sendBuffer[2] = 0x00;
  sendBuffer[3] = 0x00;
  sndSPI();
}

void printRBuffer(){
      Serial.print("Recieve Bits ");
  for(int i=0; i<4;i++){
    Serial.print(rcvBuffer[i],HEX);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void printWBuffer(){
  Serial.print("Write Bits ");
  for(int i=0; i<4;i++){
    Serial.print(sendBuffer[i],HEX);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void setup() {
  unsigned int data;
  SPI.begin();
  Serial.begin(115200);
  inital(10);
  printWBuffer();
  printRBuffer();
  data = CONV_AVG_16x | MAG_TEMPCO_0pd | OPERATING_MODE_activeMeasureMode | T_CH_EN_TempChannelEnabled | T_RATE_sameAsOtherSensors | T_HLT_EN_tempLimitCheckOff | TEMP_COMP_EN_TempCompensationDisenabled;
  sendBuffer[0] = 0x00;
  sendBuffer[1] = (byte)(data >> 8);
  sendBuffer[2] = (byte)(data & 0x00ff);
  sndSPI();
  printWBuffer();
  printRBuffer();
}

void loop() {
  readX();
  readY();
  readZ();
  delay(1000);
}
