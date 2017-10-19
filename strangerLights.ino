 #include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 150

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7

// Define the array of leds
CRGB leds[NUM_LEDS];

//Store input
int val = 0;

void setup() { 
  Serial.begin(9600);
  val = 0;
  Serial.println("resetting");
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].nscale8(250); 
  } 
}

void showSolidColor(int red, int green, int blue, int duration) {
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(green, red, blue);
  }
  FastLED.show();
  delay(duration*1000);
}

void showEveryNthColor(int red, int green, int blue, int n, int duration) {
  for(int i = 0; i < NUM_LEDS; i++){
    if(i % n == 0){
      leds[i] = CRGB(green, red, blue);
    }
    else{
      leds[i] = CRGB(0, 0, 0);
    }
  }
  FastLED.show();
  delay(duration*1000);
}

void showEveryOtherColor(int red1, int green1, int blue1, int red2, int green2, int blue2, int duration){
  for(int i = 0; i < NUM_LEDS; i++){
    if(i % 2 == 0){
      leds[i] = CRGB(green1, red1, blue1);
    }
    else{
      leds[i] = CRGB(green2, red2, blue2);
    }
  }
  FastLED.show();
  delay(duration*1000);  
}

void loop() {
  if(Serial.available()){
    val = Serial.read() - '0';
  }
  if(val != 0){
    showSolidColor(0,0,0,3);
    //2 seconds
    showSolidColor(255,0,0,6);
    //8 seconds
    showSolidColor(255, 100, 0, 6);
    //14 seconds
    for(int i = 0; i < 4; i++){
      showEveryOtherColor(255, 100, 0, 255, 0, 0, 2);
      showEveryOtherColor(255, 0, 0, 255, 100, 0, 2);
    }
    //30 seconds
    showSolidColor(255, 100, 0, 10);
    //40 seconds
    showEveryOtherColor(255, 0, 0, 0, 0, 0, 6);
    //46 seconds
    showEveryNthColor(255, 0, 0, 3, 4);
    //50 secondss
    showSolidColor(0, 0, 0, 2);
    val = 0;
  }
}
