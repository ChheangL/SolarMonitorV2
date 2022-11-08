#include "DisplayMenu.h"

extern SSD1306Wire display(0x3C, 15, 14);
screen screens[]={screen1};
void init_display(){
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}
void screen1(struct struct_data* message){
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
//  display.setFont(ArialMT_Plain_10);
//  display.drawString(0, 0,(String)"Relay: "+String(myData.relay) );
//  display.drawString(0, 11,(String)"AC_InverterPower: "+String(myData.AC_Solar_W,3)+"W" );
//  //display.drawString(0, 22,(String)"AC_InverterC: "+String(myData.AC_Solar_A,3)+"W");
//  display.drawString(0, 31,(String)"AC_InverterV: "+String(myData.AC_Solar_V,3)+"W");
//  display.drawString(0, 41,(String)"BAT_voltage: "+String(myData.voltage_battery,3)+"V");
//  display.drawString(0, 51,(String)"PV_current: "+String(myData.current_pv,3)+"A");
//  display.drawString(0, 21,(String)"AC_GRIDPower: "+String(myData.AC_usage,3)+"W");
  display.display();
  delay(10);
}
