#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H
#include <Wire.h>
#include "SSD1306Wire.h"

extern SSD1306Wire display;
//extern struct struct_message;
typedef void (*screen)(struct struct_data* message);
struct struct_data{
  bool relay;
  float AC_Solar_W ;
  float AC_Solar_A;
  float AC_Solar_V;
  float voltage_battery;
  float current_pv;
  float AC_usage;
};


void init_display();
void screen1(struct struct_data* message);

void display_menu();

#endif
