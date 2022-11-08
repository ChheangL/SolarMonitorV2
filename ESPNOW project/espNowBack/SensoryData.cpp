#include"SensoryData.h"

extern PZEM004Tv30 pzem_inverter(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN,PZEM_ADDRESS_INVERTER);
extern PZEM004Tv30 pzem_grid(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN,PZEM_ADDRESS_GRID);

float get_AC_Solar_current(){
  float temp_value = pzem_inverter.current();
  #ifdef DEBUG_MODE
    Serial.println(" AC_Solar_current: "+String(temp_value,3)+"A ");
  #endif
  return temp_value;
}

float get_AC_Solar_voltage(){
  float temp_value = pzem_inverter.voltage();
  #ifdef DEBUG_MODE
    Serial.println(" AC_Solar_voltage: "+String(temp_value,3)+"V ");
  #endif
  return temp_value;
}

float get_AC_Solar_power(){
  float temp_value = pzem_inverter.power();
  #ifdef DEBUG_MODE
    Serial.println(" AC_Solar_power: "+String(temp_value,3)+"W ");
  #endif
  return temp_value;
}

float get_ACoverall_current(){
  float temp_value = pzem_grid.current();
  #ifdef DEBUG_MODE
    Serial.println(" AC_overall_current: "+String(temp_value,3)+"A ");
  #endif
  return temp_value;
}

float get_ACoverall_voltage(){
  float temp_value = pzem_grid.voltage();
  #ifdef DEBUG_MODE
    Serial.println(" AC_overall_voltage: "+String(temp_value,3)+"V ");
  #endif
  return temp_value;
}

float get_ACoverall_power(){
  float temp_value = pzem_grid.power();
  #ifdef DEBUG_MODE
    Serial.println(" AC_overall_power: "+String(temp_value,3)+"W ");
  #endif
  return temp_value;
}


long double get_voltage(const uint8_t Analog_pin,uint32_t average){
  float x = 0;
  for(int i = 0 ; i < average ; i++){
    x += analogRead(Analog_pin);
  }
  x /= average;
  long double voltages = (long double) 0.0000000163*x*x*x - 0.0001438717*x*x + 0.4338704925*x - 395.2911431259;
  #ifdef DEBUG_MODE
    Serial.println(" voltage: "+String((float)voltages,3)+"V ");
  #endif
  return voltages;
}

long double get_pvCurrent(const uint8_t Analog_pin,uint32_t average){
  float x = 0;
  for(int i = 0 ; i<average ; i++){
    x += analogRead(Analog_pin);
  }
  x /= average;
  long double currents = (long double) 0.0000000142*x*x*x - 0.0000519004*x*x + 0.0395976118*x + 13.6667426900;
  #ifdef DEBUG_MODE
    Serial.println(" IN_Current: "+String((float)currents,3)+"A ");
  #endif
  return currents;
}
