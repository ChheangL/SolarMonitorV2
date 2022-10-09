#include <PZEM004Tv30.h>
#include <Arduino.h>
#include "WiFi.h"
#include <Firebase_ESP_Client.h>
#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Replace with your network credentials
const char* ssid = "MTech_Solution3";
const char* password = "No88138Jun2011";

#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#define PZEM_SERIAL Serial2
#define CONSOLE_SERIAL Serial
PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

// ------------- firebase init ----------
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "MTech_Solution3"
#define WIFI_PASSWORD "No88138Jun2011"

// Insert Firebase project API Key
#define API_KEY "AIzaSyD3bXGN2Fi1uaLELTpaE4WrE9MFG3Lg4qc"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://solarmonitor-b5f2c-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
unsigned long perivousRead = 0;
int count = 0;
bool signupOK = false;
unsigned float solarEnergy = 0;
// ------------------- setup ------------------
void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  solarEnergy = ReadData("solarEnergy");
}
//-------- loop --------
void loop(){
    if (millis() - sendDataPrevMillis >= 10000|| sendDataPrevMillis==0){
      sendDataPrevMillis = millis();
      sendFloat(pzem.voltage(),"ACVoltage");
      sendFloat(pzem.current(),"ACCurrent");
      sendFloat(pzem.power(),"Power");
      sendFloat(pzem.energy(),"Total_Energy");
      sendFloat(solarEnergy,"solarEnergy");
    }
  if (millis() - perivousRead >=1000){
    float voltageRead = pzem.voltage();
    float powerRead = pzem.power();
    if (voltageRead >=216.0 && voltageRead <=225.0){
      solarEnergy = solarEnergy + powerRead*1.0/3600.0;
    }  
    perivousRead = millis();
  }
}
//-------- other function --------
void sendFloat(float Data, String path){
  if (Firebase.ready() && signupOK){
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.setFloat(&fbdo, "test/"+path, Data)){
      //Serial.println("PASSED");
      //Serial.println("PATH: " + fbdo.dataPath());
      //Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }

}

void sendInt(int Data, String path){
  if (Firebase.ready() && signupOK){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "test/"+path, Data)){
      //Serial.println("PASSED");
      //Serial.println("PATH: " + fbdo.dataPath());
     // Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }    
  }
}

float ReadData(String path){
  if (Firebase.RTDB.getFloat(&fbdo, "/test/"+path)) {
      if (fbdo.dataType() == "float") {
        return fbdo.floatData();
        //Serial.println(floatValue);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
}
float ACcurrent(){
  
}
