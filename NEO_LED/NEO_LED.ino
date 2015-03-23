#include<FastLED.h>
//#include<Wire.h>

#define NUM_LEDS 62 // 62
#define DATA_PIN 12  // green wire
#define CLOCK_PIN 11  // blue wire 
//#define I2C_ADDRESS 83  // just picked a number between 0 and 255
CRGB leds[NUM_LEDS];

void setup()
{
  // chipset for Andymark strip is WS2801
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

const uint32_t PURPLE = 0xFF008F;
const uint32_t ORANGE = 0xFF1E00;

int NEO_INDEX[] = {4,37,45,36,46,35,47,49,33,8,9,10,30,51,50}; // 16 elements
int N[] = {1,39,43,37,5,36,46, 44}; // 8 elemetns

int E[] = {50,32,9,10,11,31,30,51,52}; // 9 elements

int O[] = {15,16,17,23,58,57,56,55,27};// 9 elements


void loop() {
  for (int i = 0; i < 9; i++) {
    leds[E[i]] = PURPLE;
  }
  
  for (int i = 0; i < 8; i++) {
    leds[N[i]] = PURPLE;
  }
  
  for (int i = 0; i < 9; i++) {
    leds[O[i]] = PURPLE;
  }
  
  FastLED.show();
}
