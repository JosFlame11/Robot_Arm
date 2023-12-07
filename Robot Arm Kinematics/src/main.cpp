#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#define USE_PCA9685_SERVO_EXPANDER 
#include <ServoEasing.hpp>
//#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>

#define START_DEGREE_VALUE 90
#define PWM_FREQ 50

ServoEasing J1(0x40);
ServoEasing J2(0x40);
ServoEasing J3(0x40);
ServoEasing J4(0x40);

bool stringComplete = false;
String inputString = "";


void readSerial(){
  while (Serial.available()){
    char c = (char)Serial.read();
    if(c != '\n'){
      stringComplete = true;
    } 
    else{
      inputString += c;
    }
  }
}

void doCommand(){

  //This commands are for joint to joint movement
  if (inputString.indexOf("$S1") != -1){
    String degree = inputString.substring(2);
    int d = degree.toInt();
    J1.startEaseTo(d, 20);
    }
  else if (inputString.indexOf("$S2") != -1){
    String degree = inputString.substring(2);
    int d = degree.toInt();
    J2.startEaseTo(d, 20);
    }
  else if (inputString.indexOf("$S3") != -1){
    String degree = inputString.substring(2);
    int d = degree.toInt();
    J3.startEaseTo(d, 20);
    }
  else if (inputString.indexOf("$S4") != -1){
    String degree = inputString.substring(2);
    int d = degree.toInt();
    J4.startEaseTo(d, 20);
    }

    //this commands are for Linear movement, this will only affect the end effector in x and z


}



void setup() {
  Serial.begin(9600);

  J1.attach(0, START_DEGREE_VALUE, 680, 2350);
  J2.attach(1, START_DEGREE_VALUE, 850, 2500);
  J3.attach(2, START_DEGREE_VALUE, 400, 2150);
  J4.attach(3, START_DEGREE_VALUE, 500, 2350);
  delay(500);
  
}

void loop() {

    if(stringComplete){
      inputString.trim();
      Serial.println();


      inputString = "";
      stringComplete = false;
    }
    J2.startEaseTo(90, 30);
    J3.startEaseTo(90, 30);
    J4.startEaseTo(90, 20);
    delay(1000);

}

