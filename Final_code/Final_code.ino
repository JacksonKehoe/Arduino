//Jackson Kehoe 20105920
//plan is to use bumpers to navigate, map is given so when both bumpers 
//are triggered, the robot has reached a wall
#include <Servo.h>
//creating servo function
Servo myservo1, myservo2, myservo3;
//motors and encoder set up
#define E1 5
#define M1 6
#define E2 4
#define M2 3 
#define IR A5
#define LBumper 11
#define RBumper 12
//was told the following functions were already included and written
//void rotateLeft90()
//void rotateRight90()
//void rotate180()
void ReactBumpers(){
  for(int i=0;i<12;i++){
if(digitalRead(LBumper)==LOW){L=1;}
if(digitalRead(RBumper)==LOW){R=1;}
delay(10);
}
both bumpers are triggered
 if(L==1&&R==1){ 
backwards(1000);
count++:
//count is 1 when reaches first wall, needs to turn right
if (count==1){
rotateRight90();
forward();
}
//count is 2 when reaches 2nd wall, needs to turn left
if (count==2){
  rotateleft90();
  forward();
}
//when reaches a count of 3, it has reached the location, the backwards is already 
//implemented when both bumpers are triggered, the robot stops then drops object
if (count==3){
  stop();
  myServo3.write(160);
  Serial.println("object delivered")
}
}
}
//code to make robot move forward
void forward () { 
  digitalWrite(M1, HIGH); 
  digitalWrite(M2, HIGH); 
  analogWrite(E1, 128); 
  analogWrite(E2, 128); 
}
void stop() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
void backward() { 
  digitalWrite(M1, LOW); 
  digitalWrite(M2, LOW); 
  analogWrite(E1, 128); 
  analogWrite(E2, 128); 
} 
  int dist = 10;
  int count = 0;
void setup() {
//attaching servo arms
myservo1.attach(8);
myservo2.attach(9);
myservo3.attach(10);
myservo1.write(90);
myservo2.write(160);
myservo3.write(40);
Serial.begin(9600);
  pinMode(E1, OUTPUT); 
  pinMode(E2, OUTPUT); 
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT); 
  pinMode(IR, INPUT);
}
void loop() {
  //IR sensor reading
  for(int i=0;i<12;i++){
  dist+=analogRead(IR);
  delay(10);
  }
  //calculating actual distance
  dist=dist/12;
  Serial.println(dist);
  forward();
  //10 cm from object
  if(dist>550){
  stop();
  //dont know how large object is, going to use 170 for the gripper
  myServo3.write(170);
  //rotate 180 degrees 
  rotate180();
  break();
  }
  delay(60);
  ReactBumpers();
}
