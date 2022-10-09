

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <PZEM004Tv30.h>
#include <Arduino.h>



// Replace with your network credentials
const char* ssid = "MTech_Solution3";
const char* password = "No88138Jun2011";

#if defined(ESP32)
/*************************
 *  ESP32 initialization
 * ---------------------
 * 
 * The ESP32 HW Serial interface can be routed to any GPIO pin 
 * Here we initialize the PZEM on Serial2 with RX/TX pins 16 and 17
 */
#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#endif

#define PZEM_SERIAL Serial2
#define CONSOLE_SERIAL Serial
PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

#elif defined(ESP8266)
/*************************
 *  ESP8266 initialization
 * ---------------------
 * 
 * esp8266 can connect with PZEM only via Serial0
 * For console output we use Serial1, which is gpio2 by default
 */
#define PZEM_SERIAL Serial
#define CONSOLE_SERIAL Serial1
PZEM004Tv30 pzem(PZEM_SERIAL);
#else
/*************************
 *  Arduino initialization
 * ---------------------
 * 
 * Not all Arduino boards come with multiple HW Serial ports.
 * Serial2 is for example available on the Arduino MEGA 2560 but not Arduino Uno!
 * The ESP32 HW Serial interface can be routed to any GPIO pin 
 * Here we initialize the PZEM on Serial2 with default pins
 */
#define PZEM_SERIAL Serial2
#define CONSOLE_SERIAL Serial
PZEM004Tv30 pzem(PZEM_SERIAL);
#endif

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readVoltage() {
  // Reding the voltage;
  float t = pzem.voltage();
  if (isnan(t)) {    
    Serial.println("Failed to read ");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}
String readPower() {
  // Reding the voltage;
  float t = pzem.power();
  if (isnan(t)) {    
    Serial.println("Failed to read ");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}
String readEnergy() {
  // Reding the voltage;
  float t = pzem.energy();
  if (isnan(t)) {    
    Serial.println("Failed to read ");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readCurrent() {
  // Reading the Current
  float h = pzem.current();
  if (isnan(h)) {
    Serial.println("Failed to read ");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

float solarEnergy = 0.0;
float perivousRead = 0;

String readSolar() {
  // Reading the Current
  float h = solarEnergy;
  if (isnan(h)) {
    Serial.println("Failed to read ");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 PZEM server</h2>
  <p>
    <i class="fa fa-battery-full" style="color:#059e8a;"></i> 
    <span class="dht-labels">Voltage</span> 
    <span id="temperature">%VOLTAGE%</span>
    <sup class="units">V</sup>
  </p>
  <p>
    <i class="fa fa-bolt" style="color:#00add6;"></i> 
    <span class="dht-labels">Current</span>
    <span id="humidity">%CURRENT%</span>
    <sup class="units">A</sup>
  </p>
  <p>
    <i class="fa fa fa-signal" style="color:#b007ff;"></i> 
    <span class="dht-labels">Power</span>
    <span id="humidity">%POWER%</span>
    <sup class="units">W</sup>
  </p>
  <p>
    <i class="fa fa-bolt" style="color:#7cf586;"></i> 
    <span class="dht-labels">Energy</span>
    <span id="humidity">%ENERGY%</span>
    <sup class="units">wh</sup>
  </p>
   <p>
    <i class="fa fa-bolt" style="color:#7cf586;"></i> 
    <span class="dht-labels">Solar Energy</span>
    <span id="humidity">%SOLAR%</span>
    <sup class="units">wh</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("voltage").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/voltage", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("current").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/current", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("power").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/power", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("energy").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/energy", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("solar").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/solar", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "VOLTAGE"){
    return readVoltage();
  }
  else if(var == "CURRENT"){
    return readCurrent();
  }
  else if(var == "POWER"){
    return readPower();
  }
  else if(var == "ENERGY"){
    return readEnergy();
  }
   else if(var == "SOLAR"){
    return readSolar();
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/voltage", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readVoltage().c_str());
  });
  server.on("/current", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readCurrent().c_str());
  });
  server.on("/power", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPower().c_str());
  });
  server.on("/energy", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readEnergy().c_str());
  });
  server.on("/solar", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSolar().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  if (millis() - perivousRead >=1000){
    float voltageRead = pzem.voltage();
    float powerRead = pzem.power();
    if (voltageRead >=216.0){
      solarEnergy = solarEnergy + powerRead*1.0/3600.0;
    }  
    perivousRead = millis();

  }
}
