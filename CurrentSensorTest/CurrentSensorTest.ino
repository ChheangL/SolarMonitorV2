#define CP A6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}
long double get_pvCurrent(const uint8_t Analog_pin,uint32_t average){
  float x = 0;
  for(int i = 0 ; i<average ; i++){
    x += analogRead(Analog_pin);
  }
  x /= average;
  long double currents = (long double) 0.0000000142*x*x*x - 0.0000519004*x*x + 0.0395976118*x + 13.6667426900;
  return currents;
  //return (long double)x;
}

void loop() {
  // put your main code here, to run repeatedly:
  float value1 = (float)get_pvCurrent(CP,500); 
  Serial.println(value1);
}
