#include<Servo.h>
#define LDR1 A0           //HEX of 14   ( Top    - right )    ------ 17 --------- 14 -------
#define LDR2 A1           //HEX of 15   ( Bottom - right )    ------ -- --------- -- -------
#define LDR3 A2           //HEX of 16   ( Bottom - Left  )    ------ -- --------- -- -------
#define LDR4 A3           //HEX of 17   ( Top    - Left  )    ------ 16 --------- 15 -------

#define SERVO_X 6
#define SERVO_Y 5
#define SERIALPRINT
#define SERVO_X_LIMIT 180
#define SERVO_Y_LIMIT 90

#define THRESHOLD_X (20)
#define THRESHOLD_Y (10)
#define X_GAIN (50)
#define Y_GAIN (50)

Servo servoX, servoY;

uint8_t currentAngle = 0;
uint32_t value_ldr[4]={0,0,0,0};
int32_t delta_x = 0;
int32_t delta_y = 0;
void setup() {
  servoX.attach(SERVO_X);
  servoY.attach(SERVO_Y);
  servoX.write(0);      //Rotate CCW
  servoY.write(0);      //Rotate CCW (servo Motor in front)
  delay(5000);
  servoX.write(30);    //Rotate CW
  servoY.write(30);    //Rotate CW (Servo motor in front)
  delay(3000);
  //servoX.detach();
  //servoY.detach();
  Serial.begin(115200);

}
void loop() {
  // put your main code here, to run repeatedly:
for(uint8_t i = LDR1;i<=LDR4; i++){
  uint32_t sum =0 ;
  for(uint8_t j = 0; j <150; j++){
    sum += analogRead(i);
  }
  value_ldr[i-LDR1] = sum/150;
#ifdef SERIALPRINT
  if(i == LDR1) value_ldr[0] = value_ldr[0] * 1.1;
  if(i == LDR2) value_ldr[1] = value_ldr[1] * 1.5;
     Serial.print(((String)i)+":");
    Serial.print(value_ldr[i-LDR1]);
    Serial.print(" ");
#endif
}



delta_x = value_ldr[0] - value_ldr[3];
delta_y = value_ldr[3] - value_ldr[2];
#ifdef SERIALPRINT
Serial.print(" Dx:");
Serial.print(delta_x);
Serial.print(" Dy:");
Serial.print(delta_y);
#endif


if(delta_x > THRESHOLD_X || delta_x < -THRESHOLD_X){
  int16_t pos = servoX.read()-(delta_x/X_GAIN);
  if (pos < 0) pos = 0;
  if (pos > 180) pos = 180;
  servoX.write(pos);  
#ifdef SERIALPRINT
  Serial.print(" x:"); 
  Serial.print(pos);
#endif
 }
if(delta_y > THRESHOLD_Y || delta_y < -THRESHOLD_Y){
  int16_t pos = servoY.read() + (delta_y/Y_GAIN);
  if (pos > 120) pos = 120;
  if (pos < 0) pos = 0;
  servoY.write(pos);
#ifdef SERIALPRINT
  Serial.print(" y:");
  Serial.print(pos);
#endif
}
#ifdef SERIALPRINT
Serial.println(" ");
#endif
}
