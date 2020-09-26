#define RIGHTDIR 7
#define LEFTDIR 4
#define RIGHTSPEED 6
#define LEFTSPEED 5
#define WHEELR 2
#define WHEELL 3
#define LBumper 11
#define RBumper 12
#define IR A5
int L,R=0;
void setup() {
  // put your setup code here, to run once:

  Init();
  WaitButton();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward();
  ReactBumpers();
}

void Init() {
  pinMode(LEFTSPEED, OUTPUT);
  pinMode(RIGHTSPEED, OUTPUT);
  pinMode(LEFTDIR, OUTPUT);
  pinMode(RIGHTDIR, OUTPUT);
  pinMode(WHEELR, INPUT);
  pinMode(WHEELL, INPUT);
  pinMode(LBumper, INPUT);
  pinMode(RBumper, INPUT);
}

void WaitButton(){
  while(digitalRead(LBumper)==HIGH){
    
  }
}

void forward() {
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, HIGH);
  analogWrite(LEFTSPEED, 128);
  analogWrite(RIGHTSPEED, 128);
}
void stop() {
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, 0);
  analogWrite(RIGHTSPEED, 0);
}
void turnL() {
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, 128);
  analogWrite(RIGHTSPEED, 128);
}
void turnR() {
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, HIGH);
  analogWrite(LEFTSPEED, 128);
  analogWrite(RIGHTSPEED, 128);
}

void ReactBumpers(){
  
for(int i=0;i<12;i++){
if(digitalRead(LBumper)==LOW){L=1;}
if(digitalRead(RBumper)==LOW){R=1;}
delay(10);
}
  
 if(L==1&&R==1){ 
backwards(1000);
Pivot(0,20);
forward();
Serial.print("both");
 }
 else if(L==1&&R==0){ 
backwards(1000);
Pivot(1,7);
forward();
Serial.print("left");
 }
 else if(L==0&&R==1){ 
backwards(1000);
Pivot(0,5);
forward();
Serial.print("right");
 }
 L=0;
 R=0;
}
 void backwards( int x ){
  digitalWrite(RIGHTDIR, LOW);
  digitalWrite(LEFTDIR, LOW);
  delay(x);
  //digitalWrite(M1, HIGH);
  //digitalWrite(M2, HIGH);
  
 }

 void Pivot( int d, int a){
  if(d==0){
  digitalWrite(RIGHTDIR, HIGH);
  digitalWrite(LEFTDIR, LOW);
  }
  if(d==1){
  digitalWrite(RIGHTDIR, LOW);
  digitalWrite(LEFTDIR, HIGH);
  }
  EncoderCount(a);
 }
 
 void EncoderCount(int k){
  int Count = 0;
  while(Count<k){
  while(digitalRead(WHEELL)==0){
    }
    Count++;
    if(Count==k){
    break;
    }
  while(digitalRead(WHEELL)==1){
    }
    Count++;
  }  
 }
