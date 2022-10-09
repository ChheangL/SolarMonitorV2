#include <AccelStepper.h>
AccelStepper myStepper(1,2,5); //mode, step, direction
void setup(){ 
	myStepper.setMaxSpeed(12000); //stepsPerSecond
	myStepper.setAcceleration(80); //stepsPerSecond square
	myStepper.setSpeed(9000); //stepsPerSecond
}
void loop(){
	myStepper.runSpeed();
}
