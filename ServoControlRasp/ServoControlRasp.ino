#include<Wire.h>
#include<Servo.h>

//Servo pin definition on the Arduino
#define MOTOR_SPEED_PIN   11
#define MOTOR_D1_PIN      9
#define MOTOR_D2_PIN      8
#define SERVO_PIN 6
#define SERIAL_DEBUG
/*
 * Global Variable that needed for functions
 */
bool states = false;    //indication of starting the servo function
uint8_t index = 0;      //index of the message for positioning the incomming message to struc data
uint32_t T1 = 0;        //duration time of angle 1
uint32_t T2 = 0;        //duration time of angle 2
uint32_t startTime = 0; //Time use for complaring millis()

Servo myServo;

/*
 * Structure data of the incomming message
 */
typedef struct My_datas{
  int8_t angle_1 = 90;
  uint8_t duration_1;
  int8_t angle_2 = 90;
  uint8_t duration_2;
}My_datas;

int Alt_angle1 = 90;
int Alt_angle2 = 90;

My_datas mydata;                    //initailaztion
uint8_t* pData = &mydata.angle_1;   //data pointers


/*
 * Functions for receiving event and decoding the time message
 */
void receiveEvent(int howMany){
  while(Wire.available()){
    *(pData+index) = Wire.read();   //Writing data to the pointer of data struct
    index ++;
    //When the message end at fourth term
    if(index >= 4){
      index = 0;      //reload index
      states = true;  //trigger servo restart
      check_angle();

      #ifdef SERIAL_DEBUG
      Serial.print(" : ");
      Serial.print("0x");
      Serial.print(mydata.angle_1,HEX);
      Serial.print(" ");
      Serial.print("0x");
      Serial.print(mydata.angle_2,HEX);
      Serial.print(" ");
      Serial.print("0x");
      Serial.print(mydata.duration_1,HEX);
      Serial.print(" ");
      Serial.print("0x");
      Serial.println(mydata.duration_2,HEX);
      #endif
    }
  }
}

uint32_t decodeTime(uint8_t timeCode){
  uint32_t decodedTime = (uint32_t)(timeCode>>4);       //getting the first four MSBs
  uint8_t multiplior = timeCode & (0x0F);               //resetting the first four MSBs 0000 1111
  decodedTime = (decodedTime * pow(10,multiplior))+1;   //calculating the result
  return decodedTime;
}


/*
 * Function check incomming angles are within mechanical range 45->135 degrees
 * The first nest if check angle_1 if it over the limite, if not it will just translate the angle to servo angle
 * The second nest if is the same with angle_2.
 */
void check_angle(){

  if(mydata.angle_1 <-45){
    Alt_angle1 = 45;
  }else if(mydata.angle_1 > 45){
    Alt_angle1 = 135;
  }else{
    Alt_angle1 = mydata.angle_1 + 90;
  }
  
  if(mydata.angle_2 <-45){
    Alt_angle2 = 45;
  }else if(mydata.angle_2 > 45){
    Alt_angle2 = 135;
  }else{
    Alt_angle2 = mydata.angle_2 + 90;
  }
}



void setup() {
  //I2C set up
  Wire.begin(0x08);
  Wire.onReceive(receiveEvent);

  //Servo set up
  myServo.attach(SERVO_PIN);

  //motor_init
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_SPEED_PIN,OUTPUT);
  digitalWrite(MOTOR_D1_PIN,1);
  digitalWrite(MOTOR_D2_PIN,0);
  //Serial set up
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
#endif
}

void loop() {
  //local variable
  servoControl();
}

void servoControl(){
  if(states){
    Serial.println("angle1 = "+(String)Alt_angle1);
    myServo.write(Alt_angle1);
    states = false;
    startTime = millis();
    T1 = decodeTime(mydata.duration_1);
    T2 = decodeTime(mydata.duration_2) + T1;
    analogWrite(MOTOR_SPEED_PIN,50);
#ifdef SERIAL_DEBUG
  Serial.println("T1 : "+(String)T1);
  Serial.println("T2 : "+(String)T2);
#endif
  }
  if(millis()-startTime>=T1 && millis()-startTime<= T2){
    myServo.write(Alt_angle2);
  }
  if(millis()-startTime > T2){
    analogWrite(MOTOR_SPEED_PIN,0);

  }
}
