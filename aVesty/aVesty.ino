#include <Adafruit_NeoPixel.h>

#define LEFT_STRIP_PIN 9
#define RIGHT_STRIP_PIN 11

#define LEFT_STRIP_NUM_LEDS 22
#define RIGHT_STRIP_NUM_LEDS 22

#define BRIGHTNESS_STEP 51 // step size for increasing or decreasing brightness



#define SA_COLOR_STEP 25


//#define MIC_PIN A0
//#define MIC_GAIN_PIN 6
//#define MIC_OUTPUT_MAX 1024
//#define MIC_OUTPUT_MIN 200
//#define MIC_READ_TIME 50
//
//#define WHITE_NOISE_THRESHOLD 600



int max_brightness = 255; // maximum LED brightness

Adafruit_NeoPixel left_strip = Adafruit_NeoPixel(LEFT_STRIP_NUM_LEDS, LEFT_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right_strip = Adafruit_NeoPixel(RIGHT_STRIP_NUM_LEDS, RIGHT_STRIP_PIN, NEO_GRB + NEO_KHZ800);


int pattern = 0; // current pattern

bool isOff = false;

void setup() {
  Serial.begin(115200);

 
  left_strip.setBrightness(max_brightness);
  left_strip.begin();
  left_strip.show(); // initialize all pixels to 'off'
  
  right_strip.setBrightness(max_brightness);
  right_strip.begin();
  right_strip.show(); // initialize all pixels to 'off'
  
  clearStrips();
  fft_setup();
  rainbow_setup();
  red_blue_setup();
  soundLevel_setup();
  spin_setup();
//  spectrum_analyzer_setup();
  
}

void loop() {
   // clearStrips();
//    red_blue();
//    rainbow();
//    light_FFT();
//    soundLevel();
    spin();

}

bool checkButtons() {
//  if (digitalRead(BUTTON_2_PIN) == LOW && digitalRead(BUTTON_3_PIN) == LOW) {
//    changePattern(3);
//    return false;
//  } else if (button2.update() && button2.fallingEdge()) decreaseMaxBrightness();
//  else if (button3.update() && button3.fallingEdge()) increaseMaxBrightness();
//
//  if (button1.update() && button1.fallingEdge()) {
//    changePattern();
//    return false; // pattern has changed
//  } else {
//    return true; // pattern has not changed
//  }
    return true;
}

void changePattern(int patternIn) {
  clearStrips();
  if (patternIn == -1) pattern ++;
  else pattern = patternIn;
}

void decreaseMaxBrightness() {
  max_brightness -= BRIGHTNESS_STEP;
  if (max_brightness < 0) max_brightness = 0;
}

void increaseMaxBrightness() {
  max_brightness += BRIGHTNESS_STEP;
  if (max_brightness > 255) max_brightness = 255;
}

void clearStrips() {
  for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {
    left_strip.setPixelColor(i, 0, 0, 0, 0);
  }
  for (int i=0; i < RIGHT_STRIP_NUM_LEDS; i++) {
    right_strip.setPixelColor(i, 0, 0, 0, 0);
  }
  left_strip.show();
  right_strip.show();
}

//COLORS=============================

//Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
  return left_strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
  WheelPos -= 85;
  return left_strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return left_strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 8);
}
uint8_t green(uint32_t c) {
  return (c >> 16);
}
uint8_t blue(uint32_t c) {
  return (c);
}
