#include <Servo.h>
Servo myservo1, myservo2, myservo3;
void setup(){
myservo1.attach(8);
myservo2.attach(9);
myservo3.attach(10);
}
void loop(){
myservo1.write(90);
myservo2.write(160);
myservo3.write(40);
delay(2000);
myservo3.write(180);
delay(2000);
myservo3.write(40);
}
