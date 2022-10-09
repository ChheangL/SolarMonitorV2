#include <PZEM004Tv30.h>
#define PZEM004_NO_SWSERIAL
#define ESP_RX 16
#define ESP_TX 17
#define PZEM_SERIAL Serial2
#define CONSOLE_SERIAL Serial
PZEM004Tv30 pzem(PZEM_SERIAL, ESP_RX, ESP_TX);
PZEM004Tv30 pzemNew(PZEM_SERIAL, ESP_RX, ESP_TX,0x11);

void setup() {
  // put your setup code here, to run once:
  CONSOLE_SERIAL.begin(115200);
  pzem.resetEnergy();
  CONSOLE_SERIAL.print("Custom Address:");
  CONSOLE_SERIAL.println(pzem.readAddress(), HEX);
  pzem.setAddress(0x11);
  CONSOLE_SERIAL.println(pzemNew.voltage());
}

void loop() {
  // put your main code here, to run repeatedly:

}
