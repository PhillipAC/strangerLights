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

int sensorPin = 2; //The pin the sensor is connected to
int busyPin = 3; //The pin the busy signal is set to
int sensorValue = 0; //The read from the sensor
int busyValue = 0; //The read from the busy pin
int currentSong = 1;
int songCount = 10;
int coolDown = 2; //How many seconds the device will wait before look for motion
LedService ledService; //Service to handle the lightshow
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer; //Handles playing mp3s

void setup() {
    //Set the sensor pin to input
    pinMode(sensorPin, INPUT);
    pinMode(busyPin, INPUT);
    digitalWrite(busyPin, LOW);
    mySoftwareSerial.begin(9600);
    myDFPlayer.begin(mySoftwareSerial);
    myDFPlayer.volume(30);
    myDFPlayer.disableLoop();
    myDFPlayer.playMp3Folder(currentSong);
    ledService.Begin();
    delay(coolDown * 1000);
}

// the loop function runs over and over again until power down or reset
void loop() {
    sensorValue = digitalRead(sensorPin);
    if (sensorValue == HIGH) {
        myDFPlayer.playFolder(1, 1);
        ledService.PerformLightShow();
        //Allow time before the vibration can be triggered again
        playNextSong();
        delay(coolDown * 1000);
    }
    else{
      checkSongState(myDFPlayer.readType());
    }
}

void checkSongState(uint8_t type){
  busyValue = digitalRead(busyPin);
  if(busyValue == HIGH)
  {
    playNextSong();
    delay(50);
  }
}

void playNextSong(){
      if(currentSong > songCount){
        currentSong = 1;
      }else{
        currentSong++;
      }
      myDFPlayer.playMp3Folder(currentSong);
}
