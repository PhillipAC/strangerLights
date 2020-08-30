# Stranger Sounds

## About
Stranger Sounds work with an ardiuno and a DfPlayer Mini Mp3 and a PIR Sensior to 
display a light show when a person walk up close to it. The PIR Sensior detects
the person moving near the device. When motion is detect the ardiuno sends tells
the DfPlayer module to start playing the Strang Things music while playing
a light show. When not playing the light show the DfPlayer will play music
in the folder denoted /2/. 

#Setup
Make sure to have music that will loop while the device is in a stand by in the 
folder /2/ in the SD card. The device will play the song that is in the /1/ folder
starting with 001 when motion is detected. The light show is synced with the 
theme song to Stranger Things. 

It is suggested to have a seperate power source for the LED lights than the
Arduino; although, if a source has enough current both can be controlled
by the single source.

## TODO
Start the next song after motion is detected instead of always starting with the
first song

Add a document that descibes the desired setup for the Aruduino, RBG LED Strip,
and speakers/PIR Sensor/Speaker.  