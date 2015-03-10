// LED ardiuno code to read I2C data from master and output LED lights from data


#include<FastLED.h>
//#include<Wire.h>

#define NUM_LEDS 62 // 62
#define DATA_PIN 12  // green wire
#define CLOCK_PIN 11  // blue wire 
//#define I2C_ADDRESS 83  // just picked a number between 0 and 255
CRGB leds[NUM_LEDS];
int time = 0;

struct LEDSubset {
  int lowerLED;
  int upperLED;
  int currentIndex;
  boolean goingUp;
};

void dotChase(LEDSubset &subset, uint32_t color, int timing, int time);
void oppDotChase(LEDSubset &subset, uint32_t color, int timing, int time);

void moveInRange(LEDSubset &subset);
void solid(LEDSubset &subset, uint32_t color);

LEDSubset lower;
LEDSubset middle;
LEDSubset upper;

void setup()
{
  // chipset for Andymark strip is WS2801
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  
  // Start I2C bus
  //Wire.begin(I2C_ADDRESS);
  //Wire.onReceive(i2cReceive);
  //Serial.begin(9600);  // not sure what this one is for
                         // It sets the baud rate of the serial port. Basically the speed of the two controllers talking
  
  lower.lowerLED = 2; // 0
  lower.upperLED = 18; // 20
  lower.currentIndex = 0;
  lower.goingUp = true;
  
  middle.lowerLED = 22; //21
  middle.upperLED = 39; // 40
  middle.currentIndex = 39;
  middle.goingUp = false;
  
  upper.lowerLED = 43; // 41
  upper.upperLED = 59; // 61
  upper.currentIndex = 0;
  upper.goingUp = true;
  
  
}

void loop()
{
  dotChase(lower, CRGB::Purple, 1, time);
  dotChase(middle, CRGB::Purple, 1, time);
  dotChase(upper, CRGB::Purple, 1, time);
 // oppDotChase(lower, CRGB::Red, 5, time);
  
  leds[0] = CRGB::red;
  leds[1] = CRGB::red;
  
  leds[19] = CRGB::red;
  leds[20] = CRGB::red;
  
  leds[21] = CRGB::red;
  leds[40] = CRGB::red;
  
  leds[41] = CRGB::red;
  leds[42] = CRGB::red;
  leds[60] = CRGB::red;
  leds[61] = CRGB::red;
  
  FastLED.show();
  delay(50);
  time++;
  //if (time > 500)
     //time = 0;
}
/*
void i2cReceive(int bytesRecived)  {
  
}
*/


//----------------------------------------------------------------------------- Functions for moving the LEDS -----------------------------------------------------
void dotChase(LEDSubset &subset, uint32_t color, int timing, int time)  {
  if ((time % timing) == 0) {
    solid(subset, 0xFF1E00);  // nice orange color!!!!
  
    moveInRange(subset); 
    
    leds[subset.currentIndex] = color;
    leds[subset.currentIndex + 1] = color;
  }
}

void oppDotChase(LEDSubset &subset, uint32_t color, int timing, int time)  {
  if ((time % timing) == 0) {
    solid(subset, color);
  
    moveInRange(subset); 
    
    leds[subset.currentIndex] = CRGB::Black;
  }
}




void moveInRange(LEDSubset &subset) {
  // does check for special cases where it hits end of limit
    if (subset.currentIndex >= subset.upperLED)  {
      subset.currentIndex = (subset.upperLED);
      subset.goingUp = false;
    } else if (subset.currentIndex <= subset.lowerLED) {
      subset.currentIndex = (subset.lowerLED);
      subset.goingUp = true;
    }
    
    // increments or decrements index
    if (subset.goingUp) {
      subset.currentIndex++;
    } else {
      subset.currentIndex--;
    }
}

void solid(LEDSubset &subset, uint32_t color) {
  for (int i = subset.lowerLED; i <= subset.upperLED; i++) {
    leds[i] = color;
  }
}










