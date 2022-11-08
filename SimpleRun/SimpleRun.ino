#include <SoftwareSerial.h>
#include <AccelStepper.h>



// Define the stepper motors and the pins the will use
AccelStepper LeftBackWheel(1, 2, 5);   // (Type:driver, STEP, DIR) - Stepper1
AccelStepper LeftFrontWheel(1, 3, 6);  // Stepper2
AccelStepper RightBackWheel(1, 4, 7);  // Stepper3
AccelStepper RightFrontWheel(1, 12, 13); // Stepper4

//SoftwareSerial Bluetooth(A8, 38); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
SoftwareSerial Bluetooth(0, 1); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
#define MAXSPEED 5000
int32_t wheelSpeed = 5000;
char Mode = 0;

void setup() {
 
  // Set initial seed values for the steppers
  LeftFrontWheel.setMaxSpeed(MAXSPEED);
  LeftBackWheel.setMaxSpeed(MAXSPEED);
  RightFrontWheel.setMaxSpeed(MAXSPEED);
  RightBackWheel.setMaxSpeed(MAXSPEED);
  LeftFrontWheel.setAcceleration(1);
  LeftBackWheel.setAcceleration(1);
  RightFrontWheel.setAcceleration(1);
  RightBackWheel.setAcceleration(1);
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  Serial.begin(115200);
  delay(20);
  moveSidewaysRight();
 
}
int t =0;
int d1 = 3000;
void loop() {
  int dT = millis() -t;
  if(dT <d1){
    moveSidewaysRight();
  }
  if(dT < d1*2 && dT>d1){
    moveForward();
  }
  if(dT < d1*3 && dT>d1*2){
    moveSidewaysLeft();
  }
  if(dT < d1*4 && dT>d1*3){
    moveBackward();
  }
  if(dT >= d1*4){
    t = millis();
  }
  
  LeftFrontWheel.runSpeed();
  LeftBackWheel.runSpeed();
  RightFrontWheel.runSpeed();
  RightBackWheel.runSpeed();
  
//  moveForward();
//  LeftFrontWheel.runSpeed();
//  LeftBackWheel.runSpeed();
//  RightFrontWheel.runSpeed();
//  RightBackWheel.runSpeed();
//  delay(5000);
//  moveSidewaysLeft();
//  LeftFrontWheel.runSpeed();
//  LeftBackWheel.runSpeed();
//  RightFrontWheel.runSpeed();
//  RightBackWheel.runSpeed();
//  delay(5000);
//  moveBackward();
//  LeftFrontWheel.runSpeed();
//  LeftBackWheel.runSpeed();
//  RightFrontWheel.runSpeed();
//  RightBackWheel.runSpeed();
//  delay(5000);
  
}

//----------------------------------- Function ---------------------------------
void moveForward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}

void moveBackward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}

void moveSidewaysRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}

void moveSidewaysLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}

void rotateLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}

void rotateRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}

void moveRightForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(wheelSpeed);
}

void moveRightBackward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftForward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(0);
}

void moveLeftBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(-wheelSpeed);
}

void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}
