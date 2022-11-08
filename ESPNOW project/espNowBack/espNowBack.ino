#include <esp_now.h>
#include <WiFi.h>
#include"SensoryData.h"


#define RELAY 23

typedef struct struct_message {
  bool relay = 0;
  float AC_Solar_W;
  float AC_Solar_A;
  float AC_Solar_V;
  float voltage_battery;
  float current_pv;
  float AC_usage;
} struct_message;

struct_message Data;






/*
 * ESP_NOW protocol functions
 */
extern uint8_t broadcastAddress[] = { 0x30,0xC6,0xF7,0x25,0xB2,0x08 };

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void espNow_init(){
    // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

/*
 * End of ESP_Now functions
 */

void send_data(struct_message message){
  esp_now_send(broadcastAddress, (uint8_t *)&message, sizeof(message));
}

void get_data(struct_message* myData){
  myData->AC_Solar_W = get_AC_Solar_power();
  myData->AC_Solar_A = get_AC_Solar_current();
  myData->AC_Solar_V = get_AC_Solar_voltage();
  myData->voltage_battery = (float)get_voltage(VOLTAGE_PIN,500);
  myData->current_pv = (float)get_pvCurrent(CURRENT_PIN,500);
  myData->AC_usage = get_ACoverall_power();
  Serial.println(" ");
}


void setup() {
  Serial.begin(115200);
  espNow_init();
  pinMode(RELAY,OUTPUT);
}
void loop() {
  get_data(&Data);
  send_data(Data);
  if(Data.voltage_battery < 48){
    Data.relay = 0;
    digitalWrite(RELAY,1);
  }else if (Data.voltage_battery >52){
    Data.relay = 1;
    digitalWrite(RELAY,0);
  }
  delay(1000);
}
