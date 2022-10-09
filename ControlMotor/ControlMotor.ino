#define MOTOR_SPEED_PIN 10
#define MOTOR_D1_PIN 9
#define MOTOR_D2_PIN 8
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_SPEED_PIN,OUTPUT);
  digitalWrite(MOTOR_D1_PIN,1);
  digitalWrite(MOTOR_D2_PIN,0);
  analogWrite(MOTOR_SPEED_PIN,50);
  Serial.println("Motor Started");
  delay(2000);
  analogWrite(MOTOR_SPEED_PIN,0);
  Serial.println("Motor ended");
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
