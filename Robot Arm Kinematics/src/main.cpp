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



void setup() {
  J1.attach(0, START_DEGREE_VALUE, 680, 2350);
  J2.attach(1, START_DEGREE_VALUE, 850, 2500);
  J3.attach(2, START_DEGREE_VALUE, 400, 2150);
  J4.attach(3, START_DEGREE_VALUE, 500, 2350);
  delay(500);
  
}

void loop() {
    J1.startEaseTo(90, 20);
    J2.startEaseTo(90, 30);
    J3.startEaseTo(90, 30);
    J4.startEaseTo(90, 20);
    delay(1000);

}

