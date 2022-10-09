#define CP A7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}
long double get_pvCurrent(const uint8_t Analog_pin,uint32_t average){
  float x = 0;
  for(int i = 0 ; i<average ; i++){
    x+= analogRead(Analog_pin);
  }
  x /= average;
  //long double voltages = (long double) 0.0000000109*x*x*x - 0.0000998648*x*x + 0.3156938453*x - 291.4103003013;
  //return voltages;
  return (long double)x;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println((float)get_pvCurrent(CP,500));
}
