#define encoderR 2
#define encoderL 3
#define E1       6
#define E2       5
#define M1       7
#define M2       4
#define button   9

int pressed = 0;
int state = 0;
int leftTicks = 0;
int rightTicks = 0;
int leftState = 0;
int rightState = 0;
long timer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(encoderR, INPUT);
  pinMode(encoderL, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  attachInterrupt(0, countEncoderL, CHANGE);
  attachInterrupt(1, countEncoderR, CHANGE);
  interrupts();
}

int countEncoderL() {
  int valueL = digitalRead(encoderL);
  if(valueL != leftState) {
    leftTicks++;
    leftState = valueL;
  }
}

void countEncoderR() {
  int valueR = digitalRead(encoderR);
  if(valueR != rightState) {
    rightTicks++;
    rightState = valueR;
  }
}

void drive() {
  if(leftTicks > 24) {
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
      analogWrite(E1, 128);
      analogWrite(E2, 128);   
      } 
      else if(leftTicks > 48 ) {
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      analogWrite(E1, 128);
      analogWrite(E2, 128);
      } 
      else if(rightTicks < 36) {
      digitalWrite(M1, HIGH);
      digitalWrite(M2, LOW);
      analogWrite(E1, 128);
      analogWrite(E2, 128);
      
  } else {
      analogWrite(E1, 0);
      analogWrite(E2, 0);
      return;
  }

  double elapsed = (double)(millis() - timer) / 1000;
//  Serial.println(elapsed);
  Serial.print(2*3.14*leftTicks/elapsed);
  Serial.print("\t");
  Serial.println(2*3.14*rightTicks/elapsed);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button) == HIGH) {
    if(pressed == 1) {
        pressed = 0;
        state = 1;
        timer = millis();
    }
  } else {
    pressed = 1;
  }

  if(state) {
    //countEncoder();
    drive();
  }
}
