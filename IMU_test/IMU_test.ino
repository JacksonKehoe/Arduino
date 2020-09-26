//#include <MotorControl.h>
#include <Arduino_LSM6DS3.h>

MotorControl motor(6,7,5,4);
unsigned long startTime;
unsigned long currentTime;
unsigned long rightPrevTime;
unsigned long rightCurrentTime;
unsigned long leftPrevTime;
unsigned long leftCurrentTime;
int count = 0;
double eRAccl;
double eLAccl;
double eRPos = 0;
double eLPos = 0;
float xAccelSum = 0;
float yAccelSum = 0;
float zAccelSum = 0;
float xVelSum = 0;
float yVelSum = 0;
float zVelSum = 0;
double deltaX;
float xPrevAccl, yPrevAccl, zPrevAccl;
float xCurrAccl, yCurrAccl, zCurrAccl;
float xPrevVel, yPrevVel, zPrevVel;
float xCurrVel, yCurrVel, zCurrVel;
float xPos, yPos, zPos;
double rightPRotVel = 0;
double leftPRotVel = 0;
double rightCRotVel = 0;
double leftCRotVel = 0;

String linAccelString, rotAccelString, velString, posString;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), rightCountEncoder, CHANGE); //setup interrupt for right wheel encoder
  attachInterrupt(digitalPinToInterrupt(3), leftCountEncoder, CHANGE); //setup interrupt for left wheel encoder
  interrupts();

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    while (1);
  }
}

void rightCountEncoder(){
    rightCurrentTime = millis();  //Get current time

    rightCRotVel = ((22.5/(rightCurrentTime - rightPrevTime))*3); //Calculate linear velocity (cm/ms)
    
    eRAccl = (rightCRotVel - rightPRotVel)/(rightCurrentTime - rightPrevTime);
    eRPos += rightCRotVel*(rightCurrentTime - rightPrevTime);
    eRPos /= 1000;

    rightPrevTime = rightCurrentTime;
}

void leftCountEncoder(){
    leftCurrentTime = millis(); //Get current time

    leftCRotVel = ((22.5/(leftCurrentTime - leftPrevTime))*3); //Calculate linear velocity (cm/ms)
    
    eLAccl = (leftCRotVel - leftPRotVel)/(leftCurrentTime - leftPrevTime);
    eLPos += leftCRotVel*(leftCurrentTime - leftPrevTime);
    eLPos /= 1000;

    leftPrevTime = leftCurrentTime;
}

void loop() {
  count = 0;
  motor.forward(128);
  rightPrevTime = millis();
  leftPrevTime = millis();
  startTime = millis();
  while(!IMU.accelerationAvailable())  {} //Probably shit
  IMU.readAcceleration(xPrevAccl, yPrevAccl, zPrevAccl);

//  linAccelString = "Linear acceleration: ";
//  linAccelString += xPrevAccl;
//  linAccelString += ", ";
//  linAccelString += yPrevAccl;
//  linAccelString += ", ";
//  linAccelString += zPrevAccl;
//  Serial.println(linAccelString);
//  Serial.print(xPrevAccl);
//  Serial.print("\t");
//  Serial.print(yPrevAccl);
//  Serial.print("\t");
//  Serial.print(zPrevAccl);
//  Serial.print("\t");

//  rotAccelString = "Rotational acceleration: ";
//  rotAccelString += xPrevAccl/3;
//  rotAccelString += ", ";
//  rotAccelString += yPrevAccl/3;
//  rotAccelString += ", ";
//  rotAccelString += zPrevAccl/3;
//  Serial.println(rotAccelString);
//  Serial.print(xPrevAccl/3);
//  Serial.print("\t");
//  Serial.print(yPrevAccl/3);
//  Serial.print("\t");
//  Serial.print(zPrevAccl/3);
//  Serial.print("\t");

//  rotAccelString = "Predicted right rotational acceleration: ";
//  rotAccelString += rightRotVel;
//  Serial.println(rotAccelString);
//
//  rotAccelString = "Predicted left rotational acceleration: ";
//  rotAccelString += leftRotVel;
//  Serial.println(rotAccelString);
  
  while(true) {
    if (IMU.accelerationAvailable())  {
      IMU.readAcceleration(xCurrAccl, yCurrAccl, zCurrAccl);

//      linAccelString = "Linear acceleration: ";
//      linAccelString += xCurrAccl;
//      linAccelString += ", ";
//      linAccelString += yCurrAccl;
//      linAccelString += ", ";
//      linAccelString += zCurrAccl;
//      Serial.println(linAccelString);
      Serial.print(xCurrAccl);
      Serial.print("\t");
      Serial.print(yCurrAccl);
      Serial.print("\t");
//      Serial.print(zCurrAccl);
//      Serial.print("\t");
//    
//      rotAccelString = "Rotational acceleration: ";
//      rotAccelString += xCurrAccl/3;
//      rotAccelString += ", ";
//      rotAccelString += yCurrAccl/3;
//      rotAccelString += ", ";
//      rotAccelString += zCurrAccl/3;
//      Serial.println(rotAccelString);
      Serial.print(xCurrAccl/3);
      Serial.print("\t");
      Serial.print(yCurrAccl/3);
      Serial.print("\t");
//      Serial.print(zCurrAccl/3);
//      Serial.print("\t");
          
      count++;
      currentTime = millis();
      deltaX = (currentTime-startTime)/1000;
      deltaX /= count;
      
      xAccelSum += xPrevAccl;
      xAccelSum += xCurrAccl;
      yAccelSum += yPrevAccl;
      yAccelSum += yCurrAccl;
      zAccelSum += zPrevAccl;
      zAccelSum += zCurrAccl;

      xCurrVel = (deltaX/2)*xAccelSum;
      yCurrVel = (deltaX/2)*yAccelSum;
      zCurrVel = (deltaX/2)*zAccelSum;

//      velString = "Velocity: ";
//      velString += xCurrVel;
//      velString += ", ";
//      velString += yCurrVel;
//      velString += ", ";
//      velString += zCurrVel;
//      Serial.println(velString);
      Serial.print(xCurrVel);
      Serial.print("\t");
      Serial.print(yCurrVel);
      Serial.print("\t");
//      Serial.print(zCurrVel);
//      Serial.print("\t");

//      String rotVelString = "Predicted right rotational vel: ";
//      rotVelString += rightCRotVel;
//      Serial.println(rotVelString);
//    
//      rotVelString = "Predicted left rotational vel: ";
//      rotVelString += leftCRotVel;
//      Serial.println(rotVelString);
//
//      String rotAcclString = "Predicted right rotational accl: ";
//      rotAcclString += eRAccl;
//      Serial.println(rotAcclString);
//    
//      rotAcclString = "Predicted left rotational accl: ";
//      rotAcclString += eLAccl;
//      Serial.println(rotAcclString);
//
//      String rotPosString = "Predicted right rotational pos: ";
//      rotPosString += eRPos;
//      Serial.println(rotPosString);
//    
//      rotPosString = "Predicted left rotational pos: ";
//      rotPosString += eLPos;
//      Serial.println(rotPosString);

        Serial.print(eRAccl);
        Serial.print("\t");
        Serial.print(eLAccl);
        Serial.print("\t");
        Serial.print(rightCRotVel);
        Serial.print("\t");
        Serial.print(leftCRotVel);
        Serial.print("\t");
        Serial.print(eRPos);
        Serial.print("\t");
        Serial.print(eLPos);
        Serial.print("\t");

      if (count == 1)  {
        xPrevVel = xCurrVel;
        yPrevVel = yCurrVel;
        zPrevVel = zCurrVel;
      }
      else if(count>1) {
        deltaX = (currentTime-startTime)/1000;
        deltaX /= (count - 1);
        
        xVelSum += xPrevVel;
        xVelSum += xPrevVel;
        yVelSum += yPrevVel;
        yVelSum += yPrevVel;
        zVelSum += zPrevVel;
        zVelSum += zPrevVel;

        xPos = (deltaX/2)*xVelSum;
        yPos = (deltaX/2)*yVelSum;
        zPos = (deltaX/2)*zVelSum;

//        posString = "Position: ";
//        posString += xPos;
//        posString += ", ";
//        posString += yPos;
//        posString += ", ";
//        posString += zPos;
//        Serial.println(posString);
        Serial.print(xPos);
        Serial.print("\t");
        Serial.print(yPos);
        Serial.print("\t");
//        Serial.print(zPos);
//        Serial.print("\t");

        xPrevVel = xCurrVel;
        yPrevVel = yCurrVel;
        zPrevVel = zCurrVel;
      }

      xPrevAccl = xCurrAccl;
      yPrevAccl = yCurrAccl;
      zPrevAccl = zCurrAccl;
    }
    Serial.print("\r\n");
  }
}
