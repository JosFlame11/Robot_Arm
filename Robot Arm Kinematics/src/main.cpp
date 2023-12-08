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
String data;


//For linear movement
const int L2 = 120;
const int L1 = 120;



int rad2Degree( float rad){
  return (int)(rad * 180 / PI);
  
}
void inverseKinematics(int z){
  int x = 50;
  int h = sqrt(x * x + z * z);

  float theta = acos((h/2)/L1);
  float phi = atan(x/z);

  int a1 = rad2Degree(phi + theta);
  int a2 = rad2Degree(phi - theta);
  int ra2 = 90 - theta - a2; 
  
  J2.startEaseToD(a1, 50);
  J3.easeTo(ra2, 200);  

}




void doCommand(){

  //This commands are for joint to joint movement
  if (data.indexOf("S1") != -1){
    String degree = data.substring(2);
    int dg = degree.toInt();
    J1.startEaseTo(dg, 60);
    }
  else if (data.indexOf("S2") != -1){
    String degree = data.substring(2);
    int dg = degree.toInt();
    J2.startEaseTo(dg, 60);
    }
  else if (data.indexOf("S3") != -1){
    String degree = data.substring(2);
    int dg = degree.toInt();
    J3.startEaseTo(dg, 60);
    }
  else if (data.indexOf("S4") != -1){
    String degree = data.substring(2);
    int dg = degree.toInt();
    J4.startEaseTo(dg, 60);
    }

    //this commands are for Linear movement, this will only affect the end effector in x and z
  else if (data.indexOf("LZ") != -1){
      String distance = data.substring(2);
      if (distance = 1){
        inverseKinematics(50);
        inverseKinematics(120);

      }

    }

}



void setup() {
  Serial.begin(9600);

  J1.attach(0, START_DEGREE_VALUE, 680, 2350);
  J2.attach(1, START_DEGREE_VALUE, 850, 2500);
  J3.attach(2, START_DEGREE_VALUE, 400, 2150);
  J4.attach(3, START_DEGREE_VALUE, 500, 2350);
  delay(500);
  J3.setReverseOperation(true);
  
}

void loop() {

    if (Serial.available()){
    data = Serial.readString();
    data.trim();

    Serial.println(data);

    doCommand();

  }
}
