/*
 Name:    MotionStrangerLights.ino
 Created: 8/23/2020 8:46:35 AM
 Author:  phillip clontz
*/

// the setup function runs once when you press reset or power the board
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <FastLED.h>
#include <Arduino.h>

#include "LedService.h"

int sensor = 2; //The pin the sensor is connected to
int lightPin = 12; //The pins the motor is set to
int val = 0; //The read from the sensor
int coolDown = 10; //How many seconds the device will wait before look for motion
LedService ledService(lightPin); //Service to handle the lightshow
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer; //Handles playing mp3s

void setup() {
    //Set the sensor pin to input
    pinMode(sensor, INPUT);
    mySoftwareSerial.begin(9600);
    myDFPlayer.begin(mySoftwareSerial);
    myDFPlayer.volume(30);
    myDFPlayer.loopFolder(2);
    ledService.Begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
    val = digitalRead(sensor);
    //val = LOW;
    if (val == HIGH) {
        myDFPlayer.playFolder(1, 1);
        ledService.PerformLightShow();
        //Allow time before the vibration can be triggered again
        myDFPlayer.loopFolder(2);
        delay(coolDown * 1000);
    }
}
