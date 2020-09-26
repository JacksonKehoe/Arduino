#define leftWheelE 6 

#define leftWheelM 7 

#define rightWheelE 5 

#define rightWheelM 4 

#define LEDPIN 13 

#define BUTTON 9 

#define Encode 2 

#define EncodeL 3 

int count; 

int check; 

int bstate; 

int hold; 

int state; 

int stateL; 

int oldCheck; 

int oldCount; 

unsigned long nowL; 

unsigned long nowR; 

unsigned long beforeL; 

unsigned long beforeR; 

double velL; 

double velR; 

void setup() { 

  // put your setup code here, to run once: 

  pinMode(leftWheelE, OUTPUT); 

  pinMode(rightWheelE, OUTPUT); 

  pinMode(leftWheelM, OUTPUT); 

  pinMode(rightWheelM, OUTPUT); 

  pinMode(Encode, INPUT); 

  state = digitalRead(Encode); 

  beforeL = millis(); 

  beforeR = millis(); 

  oldCheck = 0; 

  oldCount = 0; 

  attachInterrupt(0, transition, CHANGE); 

  attachInterrupt(1, transitionL, CHANGE); 

  Serial.begin(9600); 

} 

  

void loop() { 

  // put your main code here, to run repeatedly: 

  bstate = digitalRead(BUTTON); 

  if (bstate == 0) { 

    hold = 1; 

  } 

  if (bstate == 1 && hold == 1) { 

    digitalWrite(LEDPIN, HIGH); 

  

    if (count < 48) { 

      forward(); 

    } 

    else if (count >= 48 && count < 80) { 

      backward(); 

    } 

    else if (count >= 80 && count < 84) { 

      turn(); 

    } 

    else { 

      stop(); 

    } 

    Serial.print("Left wheel rotation velocity: "); 

    speedL(); 

    Serial.println(" cm/s"); 

    Serial.print("Right wheel rotation velocity: "); 

    speedR(); 

    Serial.println(" cm/s"); 

    delay(1000); 

  } 

  

  

} 

void forward () { 

  digitalWrite(leftWheelM, HIGH); 

  digitalWrite(rightWheelM, HIGH); 

  analogWrite(leftWheelE, 128); 

  analogWrite(rightWheelE, 128); 

} 

void backward() { 

  digitalWrite(leftWheelM, LOW); 

  digitalWrite(rightWheelM, LOW); 

  analogWrite(leftWheelE, 128); 

  analogWrite(rightWheelE, 128); 

} 

void turn() { 

  digitalWrite(leftWheelM, HIGH); 

  digitalWrite(rightWheelM, LOW); 

  analogWrite(leftWheelE, 128); 

  analogWrite(rightWheelE, 128); 

} 

void stop() { 

  digitalWrite(leftWheelM, LOW); 

  digitalWrite(rightWheelM, LOW); 

  analogWrite(leftWheelE, 0); 

  analogWrite(rightWheelE, 0); 

} 

void transition() { 

  if (digitalRead(Encode) != state ) { 

    count++; 

    state = digitalRead(Encode); 

  } 

} 

void transitionL() { 

  if (digitalRead(EncodeL) != stateL ) { 

    check++; 

    state = digitalRead(EncodeL); 

  } 

} 

void speedL() { 

  nowL = millis(); 

  velL = ((check - oldCheck)*1.18)/((nowL - beforeL)/1000); 

  beforeL = nowL; 

  oldCheck = check; 

  Serial.print(velL); 

} 

void speedR() { 

  nowR = millis(); 

  velR = ((count - oldCount)*1.18)/((nowR - beforeR)/1000); 

  beforeR = nowR; 

  oldCount = count; 

  Serial.print(velR); 

} 
