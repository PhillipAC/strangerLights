// Led.h

#include <FastLED.h>

#define NUM_LEDS 150

class LedService
{
 protected:
     CRGB Leds[NUM_LEDS];
     int LedCount;

 public:
     LedService(uint8_t dataPin)
     {
         LedCount = NUM_LEDS;
         LEDS.addLeds<WS2812, dataPin, GRB>(Leds, NUM_LEDS);
         LEDS.setBrightness(84);
     };

     void Begin()
     {
         ShowEveryOtherColor(CHSV(25, 255, 255), CHSV(200, 255, 255), 0.001);
     };

     void ShowEveryNthColor(CHSV color, int n, double duration) {
         for (int i = 0; i < LedCount; i++) {
             if (i % n == 0) {
                 Leds[i] = color;
             }
             else {
                 Leds[i] = CRGB(0, 0, 0);
             }
         }
         FastLED.show();
         delay(round(duration * 1000));
     };

     void Fadeall() {
         for (int i = 0; i < NUM_LEDS; i++) {
             Leds[i].nscale8(250);
         }
     }

     void ShowSolidColor(CHSV color, double duration) {
         for (int i = 0; i < NUM_LEDS; i++) {
             Leds[i] = color;
         }
         FastLED.show();
         delay(round(duration * 1000));
     }

     void ShowEveryOtherColor(CHSV color1, CHSV color2, double duration) {
         for (int i = 0; i < NUM_LEDS; i++) {
             if (i % 2 == 0) {
                 Leds[i] = color1;
             }
             else {
                 Leds[i] = color2;
             }
         }
         FastLED.show();
         delay(round(duration * 1000));
     }

     void PerformLightShow()
     {
         delay(3.6 * 1000);
         //1 second
         ShowSolidColor(CHSV(0, 255, 255), 5.4);
         //8 seconds
         ShowSolidColor(CHSV(25, 255, 255), 6);
         //14 seconds
         //duration 16
         for (int i = 0; i < 12; i++) {
             ShowEveryOtherColor(CHSV(25, 255, 255), CHSV(200, 255, 255), 2 * 0.3571);
             ShowEveryOtherColor(CHSV(200, 255, 255), CHSV(25, 255, 255), 2 * 0.3571);
         }
         //30 seconds
         ShowSolidColor(CHSV(25, 255, 255), 9);
         //40 seconds
         ShowEveryOtherColor(CHSV(0, 255, 255), CHSV(0, 0, 0), 6);
         //46 seconds
         ShowEveryNthColor(CHSV(0, 255, 255), 3, 3);
         //50 secondss
         ShowEveryOtherColor(CHSV(25, 255, 255), CHSV(200, 255, 255), 0.001);
     }
};




