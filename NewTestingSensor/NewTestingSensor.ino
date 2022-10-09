#include <TMAG5170.h>
TMAG5170 mySensor(10);
void setup() {
 Serial.begin(115200);
 mySensor.initTMAG5170_forEval();
}

void loop() {
  Serial.println(mySensor.readRegData(0x09),BIN);
  Serial.println(mySensor.readRcvData(0x09)),BIN;
  delay(1000);
}
