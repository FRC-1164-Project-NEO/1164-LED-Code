#include <FastLED.h>

#define NUM_LEDS 62 // 62
#define DATA_PIN 12  // green wire
#define CLOCK_PIN 11  // blue wire 
CRGB leds[NUM_LEDS];
int time = 0;

const uint32_t PURPLE = 0xFF008F;
const uint32_t ORANGE = 0xFF1E00;

struct LEDSubset {
  int lowerLED;
  int upperLED;
  int currentIndex;
  boolean goingUp;
};

// full function for sending the LEDS up and down the strip
void stripChases(uint32_t color);
void Fire2012(); // run simulation frame
void solid(LEDSubset &subset, uint32_t color);
void crazyLights();
void solidAll(uint32_t color);
void alternatingLEDS(uint32_t one, uint32_t two);


void dotChase(LEDSubset &subset, uint32_t color, int timing, int time);
void oppDotChase(LEDSubset &subset, uint32_t color, int timing, int time);
void moveInRange(LEDSubset &subset);
void heatColor(int index, byte heat);

LEDSubset lower;
LEDSubset middle;
LEDSubset upper;


#define OFF 0
#define RED_RUN 1
#define BLUE_RUN 2
#define SOLID_RED 3
#define SOLID_BLUE 4
#define NEO_FIRE 5
#define CRAZY_LIGHT 6
#define ALTERNATING 7


#define FRAMES_PER_SECOND 60
#define COOLING 40
#define SPARKING 50

const int high = HIGH;
const int low = LOW;



void setup()
{
  // chipset for Andymark strip is WS2801
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  
  
  lower.lowerLED = 2; // 0
  lower.upperLED = 18; // 20
  lower.currentIndex = 0;
  lower.goingUp = true;
  
  middle.lowerLED = 23; //21
  middle.upperLED = 39; // 40
  middle.currentIndex = 39;
  middle.goingUp = false;
  
  upper.lowerLED = 43; // 41
  upper.upperLED = 59; // 61
  upper.currentIndex = 0;
  upper.goingUp = true;
  
  
  pinMode(OFF, INPUT_PULLUP);
  pinMode(RED_RUN, INPUT_PULLUP);
  pinMode(BLUE_RUN, INPUT_PULLUP);
  pinMode(SOLID_RED, INPUT_PULLUP);
  pinMode(SOLID_BLUE, INPUT_PULLUP);
  pinMode(NEO_FIRE, INPUT_PULLUP);
  pinMode(CRAZY_LIGHT, INPUT_PULLUP);
  pinMode(ALTERNATING, INPUT_PULLUP);
}



void loop()
{
  if (digitalRead(OFF) == high) {
    solidAll(CRGB::Black);
  } else if (digitalRead(RED_RUN) == high) {
    stripChases(CRGB::Red);
  } else if (digitalRead(BLUE_RUN) == high) {
    stripChases(CRGB::Blue);
  } else if (digitalRead(SOLID_BLUE) == high) {
    solidAll(CRGB::Blue);
  } else if (digitalRead(SOLID_RED) == high) {
    solidAll(CRGB::Red);
  } else if (digitalRead(CRAZY_LIGHT) == high) {
    solidAll(CRGB::Red);
  } else if (digitalRead(ALTERNATING) == high) {
    alternatingLED(PURPLE, ORANGE);
  } else if (digitalRead(NEO_FIRE) == high) {
    Fire2012();
  }
  
  
  
  
  
  
  
  FastLED.show();
  
  time++;
}



// --------------------------------------------------------------- Different Strip settings settings -----------------------------------------------------

// full function for sending the LEDS up and down the strip
void stripChases(uint32_t color) {
  dotChase(lower, PURPLE, 1, time);
  dotChase(middle, PURPLE, 1, time);
  dotChase(upper, PURPLE, 1, time);
  
  //uint32_t color = CRGB::Blue;
  
  leds[0] = color;
  leds[1] = color;
  
  leds[19] = color;
  leds[20] = color;
  
  leds[21] = color;
  leds[22] = color;
  leds[40] = color;
  
  leds[41] = color;
  leds[42] = color;
  leds[60] = color;
  leds[61] = color;
  
  delay(50);
}

void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
        //leds[j] = HeatColor( heat[j]);
        heatColor(j, heat[j]);
    }
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}
void crazyLights() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = random(0, 255);
    leds[i].g = random(0,255);
    leds[i].b = random(0,255);
    
  }
}


void solidAll(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++)
     leds[i] = color;
  delay(100);
}

void alternatingLEDS(uint32_t one, uint32_t two) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if ((i % 2) == 0)
       leds[i] = one;
    else
       leds[i] = two;
  }
  delay(100);
}

// ----------------------------------------------------------------------- Fire functions ----------------------------------------------------------------------

void heatColor(int index, byte heat) {
  /*
  leds[index].r = heat; //(heat * (25/255)) + (255-255);
  if ((heat - 50) > 0) {
    leds[index].b = heat - 50;
  }
  else
    leds[index].b = 0;
    */
    
    if (heat > 127) {
      //leds[index] = PURPLE;
      leds[index].r = heat;
      leds[index].b = heat - 50;
    }
    else {
      
      int red = 255;
      int green = 28;
      leds[index].r = red;
      leds[index].g = green;
       
    }
}


//----------------------------------------------------------------------------- Functions for moving the LEDS -----------------------------------------------------

void dotChase(LEDSubset &subset, uint32_t color, int timing, int time)  {
  if ((time % timing) == 0) {
    solid(subset, ORANGE);  // nice orange color!!!!
  
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










