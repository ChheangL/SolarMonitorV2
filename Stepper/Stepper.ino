void setup() {
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(13,INPUT);
 digitalWrite(2,HIGH);
}
bool previous=1;
bool reading =0;
unsigned int t=400;
bool dir = 1;
unsigned int pT =0;

void loop() {
  // put your main code here, to run repeatedly:
  reading = digitalRead(13);
  
  if(reading && !previous){
    dir = !dir;
    digitalWrite(2,dir);
  }
  previous = reading;
  digitalWrite(3,1);
  delayMicroseconds(t);
  digitalWrite(3,0);
  delayMicroseconds(t);  
}
