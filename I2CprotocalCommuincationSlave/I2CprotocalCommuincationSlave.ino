#include<Wire.h> //is the i2c library
#include<Servo.h>

#define MOTOR_SPEED_PIN   10
#define MOTOR_D1_PIN      9
#define MOTOR_D2_PIN      8
#define SERVO_PIN         6
Servo myServo;

typedef struct My_datas{
  int8_t angle_1;
  int8_t angle_2;
  uint8_t duration_1;
  uint8_t duration_2;
}My_datas;

My_datas data1;
bool states = false;
uint8_t i = 0;
uint8_t* pData = &data1.angle_1;

void engine(uint8_t speed_value){
  /*
   *The start _engine function will start and stop the enigne when given period. 
   *and an incomming message will renew the function.         
   */
  digitalWrite(MOTOR_D1_PIN,0);
  digitalWrite(MOTOR_D1_PIN,1);
  analogWrite(MOTOR_SPEED_PIN,speed_value);
}
uint32_t decodeTime(uint8_t timeCode){
  uint32_t duration = (uint32_t)(timeCode >> 4);
  uint8_t temp = timeCode & (0x0F);
  duration = (duration * pow(10,temp))+1;
  return duration;
}

void check_angle(){
  /*
   * Function check incomming angles are within mechanical range 45->135 degrees
   * The first nest if check angle_1 if it over the limite, if not it will just translate the angle to servo angle
   * The second nest if is the same with angle_2.
   */
  if(data1.angle_1 <-45){
    data1.angle_1 = 45;
  }else if(data1.angle_1 > 45){
    data1.angle_1 = 135;
  }else{
    data1.angle_1 = data1.angle_1 + 90;
  }
  
  if(data1.angle_2 <-45){
    data1.angle_2 = 45;
  }else if(data1.angle_2 > 45){
    data1.angle_2 = 135;
  }else{
    data1.angle_2 = data1.angle_2 + 90;
  }
}


void receiveEvent(int howMany){
  while(Wire.available()){
    *(pData+i) = Wire.read();
    i ++;
    if(i>=0x04) {
      i=0x00;
      check_angle();
      Serial.print(" : ");
      Serial.print("0x");
      Serial.print(data1.angle_1,HEX);
      Serial.print(" ");
      Serial.print("0x");
      Serial.print(data1.angle_2,HEX);
      Serial.print(" ");
      Serial.print("0x");
      Serial.print(data1.duration_1,HEX);
      Serial.print(" ");
      Serial.print("0x");
      Serial.println(data1.duration_2,HEX);
      states = true;
          }
  }
}


void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x08); // slave address 8
  Wire.onReceive(receiveEvent);

  //Servo
  myServo.attach(SERVO_PIN);
  Serial.begin(115200);

  //motor_init
  pinMode(MOTOR_SPEED_PIN,OUTPUT);
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
}





uint32_t startTime =0 ;

void loop() {
  // put your main code here, to run repeatedly:
  if(states){
    myServo.write(data1.angle_1);
    states = false;
    startTime = millis();
    engine(255/2);
    duration1 = decodeTime(data1.duration_1);
    Serial.println(duration1);
    duration2 = decodeTime(data1.duration_2);
    Serial.println(duration2);
  }
  if(millis() - startTime >= duration1 && millis()-startTime <= (duration1+duration2))
  {
    myServo.write(data1.angle_2);
  }
  if(millis()-startTime >= (duration1+duration2))
}
