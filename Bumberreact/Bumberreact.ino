#define leftWheelE 6
#define leftWheelM 7
#define rightWheelE 5
#define rightWheelM 4
#define Encode 2
#define EncodeL 3
#define LBumper 11
#define RBumper 12



void setup() {
 
  //WaitButton();
  

  pinMode(leftWheelE, OUTPUT);
  pinMode(rightWheelE, OUTPUT);
  pinMode(leftWheelM, OUTPUT);
  pinMode(rightWheelM, OUTPUT);
  pinMode(Encode, INPUT);
  pinMode(EncodeL, INPUT);

}


void backward() {
  digitalWrite(leftWheelM, LOW);
  digitalWrite(rightWheelM, LOW);
  analogWrite(leftWheelE, 128);
  analogWrite(rightWheelE, 128);
}
void forward() {
  digitalWrite(leftWheelM, HIGH);
  digitalWrite(rightWheelM, HIGH);
  analogWrite(leftWheelE, 128);
  analogWrite(rightWheelE, 128);
}
void stop() {
  digitalWrite(leftWheelM, LOW);
  digitalWrite(rightWheelM, LOW);
  analogWrite(leftWheelE, 0);
  analogWrite(rightWheelE, 0);
}
void turn() {
  digitalWrite(leftWheelM, HIGH);
  digitalWrite(rightWheelM, LOW);
  analogWrite(leftWheelE, 128);
  analogWrite(rightWheelE, 128);
  }
void loop() {
  forward();
  ReactBumpers();
}

void ReactBumpers()
{
  LBumper=analogRead(LBumper);
  RBumper=analogRead(RBumber);
  if(BumperL == HIGH && BumperR == HIGH){
    turn();
}
  else if(BumperL == HIGH){
    turn();
    backward();
  }
  else if(BumperR == HIGH){
    turn();
    backward();
  }
}
