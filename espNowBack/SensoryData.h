#ifndef SENSORYDATA_H
#define SENSORYDATA_H

#include <PZEM004Tv30.h>
#include "Arduino.h"
#define DEBUG_MODE



#define VOLTAGE_PIN             A7
#define CURRENT_PIN             A6
#define VOLTAGE_AVERAGE         500U
#define CURRENT_AVERAGE         500U
#define VCC_VALUE               3.24F
#define K_VALUE                 0.01F
#define PZEM_ADDRESS_INVERTER   0x11
#define PZEM_ADDRESS_GRID       0x12
#define PZEM_RX_PIN             16
#define PZEM_TX_PIN             17
#define RES1                    2000000U
#define RES2                    100000U
#define PZEM_SERIAL             Serial2


extern PZEM004Tv30 pzem_inverter;
extern PZEM004Tv30 pzem_grid;



float get_AC_Solar_current();
float get_AC_Solar_voltage();
float get_AC_Solar_power();
float get_ACoverall_current();
float get_ACoverall_voltage();
float get_ACoverall_power();

long double get_voltage(const uint8_t Analog_pin,uint32_t average);
long double get_pvCurrent(const uint8_t Analog_pin,uint32_t average);



#endif
