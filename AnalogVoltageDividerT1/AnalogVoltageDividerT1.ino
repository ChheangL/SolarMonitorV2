#define VOLTAGE_PIN 34
#define RESISTOR1 1950000U
#define RESISTOR2 98200U
#define AVERAGE   500
#include "esp_adc_cal.h"

void setup() {
  Serial.begin(115200);
  pinMode(VOLTAGE_PIN,INPUT);
  analogReadResolution(12);
}

void loop() {
  float sum = 0;
  //for(int i=0; i<AVERAGE;i++){
   sum = analogRead(VOLTAGE_PIN);
  //}
  //sum = (float)(sum/ AVERAGE);

  float sum2 = ReadVoltage(VOLTAGE_PIN);
  Serial.print((sum*3.23)/4095.0);
  Serial.print(" _ ");
  Serial.print((sum2*3.23)/4095.0);
  Serial.print(" _ ");

  float voltage = (float)((sum*3.23)/4095.0)*((RESISTOR1 +RESISTOR2)/(RESISTOR2));
  Serial.println(voltage);
}

float ReadVoltage(byte ADC_Pin) {
  float calibration  = 1.000; // Adjust for ultimate accuracy when input is measured using an accurate DVM, if reading too high then use e.g. 0.99, too low use 1.01
  float vref = 1100;
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  vref = adc_chars.vref; // Obtain the device ADC reference voltage
  return (analogRead(ADC_Pin) / 4095.0) * 3.3 * (1100 / vref) * calibration;  // ESP by design reference voltage in mV
}