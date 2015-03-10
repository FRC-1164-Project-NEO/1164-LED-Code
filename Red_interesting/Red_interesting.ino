#include<FastLED.h>
//#include<Wire.h>

#define NUM_LEDS 62 // 62
#define DATA_PIN 12  // green wire
#define CLOCK_PIN 11  // blue wire 
//#define I2C_ADDRESS 83  // just picked a number between 0 and 255
CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = random(225, 255);
    leds[i].g = random(0,25);
    leds[i].b = random(0,25);
  }
  FastLED.show();
  delay(50);
}
