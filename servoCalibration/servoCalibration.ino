#include<Servo.h>

#define SERVO_PIN 6

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.writeMicroseconds(572);
  delay(1000);
  myServo.writeMicroseconds(1400);
  delay(1000);
  myServo.writeMicroseconds(2300);
  delay(1000);

}
