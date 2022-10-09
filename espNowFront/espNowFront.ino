#include<esp_now.h>
#include <WiFi.h>
#include "DisplayMenu.h"
//const int MAX_ESP_NOW_PACKET_SIZE = 250;
//
//typedef struct struct_message {
//  bool relay = 0;
//  float AC_Solar_W =0 ;
//  float AC_Solar_A=0;
//  float AC_Solar_V=0;
//  float voltage_battery=0;
//  float current_pv=0;
//  float AC_usage=0;
//} struct_message;

//struct_message myData;
struct struct_data data1;
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&data1, incomingData, sizeof(data1));
//  Serial.println("Relay1: "+String(myData.relay));
//  Serial.println("AC_InverterPower: "+String(myData.AC_Solar_W,3)+"W");
//  Serial.println("AC_InverterC: "+String(myData.AC_Solar_A,3)+"W");
//  Serial.println("AC_InverterV: "+String(myData.AC_Solar_V,3)+"W");
//  Serial.println("BAT_voltage: "+String(myData.voltage_battery,3)+"V");
//  Serial.println("PV_current: "+String(myData.current_pv,3)+"A");
//  Serial.println("AC_GRIDPower: "+String(myData.AC_usage,3)+"W");
//  Serial.println(" ");
  
  //digitalWrite(2,myData.relay);
}

void setup() {
  
  
  // Setup Serial Monitor
  Serial.begin(115200);
 
  // Put ESP32 into Station mode
  WiFi.mode(WIFI_STA);

 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  
}

//uint8_t address[]= {0x8C,0xAA,0xB5,0x8B,0x6D,0x34};
//24:A1:60:C5:6A:68 MacEspCam
