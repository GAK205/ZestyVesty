#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>


#define LEFT_STRIP_PIN 9
#define RIGHT_STRIP_PIN 11

#define LEFT_STRIP_NUM_LEDS 22
#define RIGHT_STRIP_NUM_LEDS 22

#define BRIGHTNESS_STEP 51 // step size for increasing or decreasing brightness

#define SA_COLOR_STEP 25


#define BUTTON_PIN_1 3 //Next Button
#define BUTTON_PIN_2 5 //Prev Button

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


// Instantiate NEXT Bounce object
Bounce debouncer1 = Bounce(); 

// Instantiate PREV Bounce object
Bounce debouncer2 = Bounce(); 

//Light Pattern
int pattern = 0; // current pattern

void setup() {
  Serial.begin(115200);

// Setup buttons with an internal pull-up : ==================
  pinMode(BUTTON_PIN_1,INPUT_PULLUP);
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(5); // interval in ms
  
  pinMode(BUTTON_PIN_2,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(5); // interval in ms


//Initalize LED Strips: ======================================
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
  
}

void loop() {
  pattern = 2;
  
  if (pattern == 0) {
    Serial.println("Blank Pattern");
    blankStrips();  
  }
  else if (pattern == 1) {
    Serial.println("Rainbow Pattern");
    rainbow();
  }
  else if (pattern == 2) {
    Serial.println("FFT Pattern");
    light_FFT();
  }
  else if (pattern == 3) {
    Serial.println("Volume Pattern");
    soundLevel();
  }
  else if (pattern == 4){
    Serial.println("Spin Pattern");
    spin();
  }
  else if (pattern == 5){
    Serial.println("Police Pattern");
    red_blue();
  }
  else{
    pattern = 0;
  }

}

bool checkButtons() {
  
  debouncer1.update();
  debouncer2.update();
  
  if (debouncer1.fallingEdge()) {
//    Serial.println("next Pattern");
    
    int nextPattern = pattern + 1;
    changePattern(nextPattern);
    return false;
  } 
  else if (debouncer2.fallingEdge()) {
//    Serial.println("prev Pattern");
    
    int prevPattern = pattern - 1;
    changePattern(prevPattern);
    return false;
  }
  else{
    return true;
  }
}

void changePattern(int patternIn) {
  clearStrips();
  //loop forwards
  if (patternIn > 5){
    pattern = 0;
  }
  //loop backwards
  else if (patternIn < 0){
    pattern = 5;
  }
  else{
    pattern = patternIn;
  }
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

void blankStrips() {
  while(checkButtons()){
    for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {
      left_strip.setPixelColor(i, 0, 0, 0, 0);
    }
    for (int i=0; i < RIGHT_STRIP_NUM_LEDS; i++) {
      right_strip.setPixelColor(i, 0, 0, 0, 0);
    }
    left_strip.show();
    right_strip.show();
  }
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
