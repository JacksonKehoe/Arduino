//wifi code for robot
#ifndef QSerial_h
#define QSerial_h
#include "QSerial.h"
#include<SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "MPU6050.h"
QSerial myIR;
int tmp;
RF24 radio(7,8);
const byte address[6] = "00001";
MPU6050 imu;

void setup() {
  Serial.begin(9600);
  myIR.attach(5, -1); //bug eye sensor attached to pin5
  radio.begin();
  radio.openWritingPipe(address);
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  radio.startListening();
  imu.initialize();
  }
void loop() {
  const char text[] = "Home Plate Found!"
  tmp = myIR.receive(500);
  location = Serial.read(imu);
    if(tmp != 0){
      stop();//assuming stop command is written for robot
      radio.write(&text, sizeof(text));
      Serial.println(&text, sizeof(text));
      homeplate = Serial.read(imu);
      radio.startListening();
      if (radio.available()){
        radio.read(&text,sizeof(text));
        radio.read(homeplate);
        radio.write(homeplate); 
      }
      else{
        Serial.println("error connecting to wifi receiver");
        break;
      }
      radio.stopListening();{
      if(location!=homeplate){
      moveToHome();//assuming move to home command written by superteam
      }
      else if(location==home)
      {
        Serial.println("robot found home");
        stop();
      }
      else
      {
        continue;
      }
      delay(1000);
        //based on super team division, homeplate search team should have
        //an if statement that sees if location matches that of the radio
        //if it doesnt, the other 2 robots should move to the location
        //and the one that matches should stay still
  }
  else{
    continue;
    }
  }
