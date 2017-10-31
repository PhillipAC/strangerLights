#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 150

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 9

// Define the array of leds
CRGB leds[NUM_LEDS];

//Store input
int val = 0;

void setup() { 
  Serial.begin(9600);
  val = 0;
  Serial.println("resetting");
  LEDS.addLeds<WS2812,DATA_PIN,GRB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
  showEveryOtherColor(CHSV(25, 255, 255), CHSV(200, 255, 255), 0.001);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].nscale8(250); 
  } 
}

void showSolidColor(CHSV color, double duration) {
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = color;
  }
  FastLED.show();
  delay(round(duration*1000));
}

void showEveryNthColor(CHSV color, int n, double duration) {
  for(int i = 0; i < NUM_LEDS; i++){
    if(i % n == 0){
      leds[i] = color;
    }
    else{
      leds[i] = CRGB(0, 0, 0);
    }
  }
  FastLED.show();
  delay(round(duration*1000));
}

void showEveryOtherColor(CHSV color1, CHSV color2, double duration){
  for(int i = 0; i < NUM_LEDS; i++){
    if(i % 2 == 0){
      leds[i] = color1;
    }
    else{
      leds[i] = color2;
    }
  }
  FastLED.show();
  delay(round(duration*1000));  
}

//Not functional yet
void slideColor(CHSV color1, CHSV color2, int duration){
  int xHue = color2.hue - color1.hue;
  int xSat = color2.sat - color1.sat;
  int xVal = color2.val - color1.val;
  double iHue = (double)xHue/(duration*1000);
  double iSat = (double)xSat/(duration*1000);
  double iVal = (double)xVal/(duration*1000);
  for(int i = 0; i < duration*1000; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      leds[j] = CHSV(round(color1.hue+iHue*i), round(color1.sat+iSat*i), round(color1.val+iVal*i));
    }
    FastLED.show();
  }
}

void loop() {
  if(Serial.available()){
    val = Serial.read() - '0';
  }
  if(val != 0){
    delay(3.6*1000);
    //1 second
    showSolidColor(CHSV(0,255,255),5.4);
    //8 seconds
    showSolidColor(CHSV(25, 255, 255), 6);
    //14 seconds
    //duration 16
    for(int i = 0; i < 12; i++){
      showEveryOtherColor(CHSV(25, 255, 255), CHSV(200, 255, 255), 2*0.3571);
      showEveryOtherColor(CHSV(200,255,255), CHSV(25,255,255), 2*0.3571);
    }
    //30 seconds
    showSolidColor(CHSV(25,255,255), 9);
    //40 seconds
    showEveryOtherColor(CHSV(0,255,255),CHSV(0,0,0), 6);
    //46 seconds
    showEveryNthColor(CHSV(0,255,255), 3, 3);
    //50 secondss
    showEveryOtherColor(CHSV(25, 255, 255), CHSV(200, 255, 255), 0.001);
    val = 0;
  }
}
