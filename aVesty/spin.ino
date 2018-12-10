#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;

float a;

int lastMove;
//update only after the movement has stopped
int checkTime = 2000; //2s

void spin_setup()
{
  a = accel.cz; //initialze to the z accel
}

// The loop function will simply check for new data from the
//  accelerometer and print it out if it's available.

void spin()
{
   accel.init(SCALE_2G, ODR_100); //data collection rate and acceleration scale

    lastMove = 0;
   
    while(checkButtons()){ //button clicking
      if (accel.available()){
      // First, use accel.read() to read the new variables:
      accel.read();
      // Then, call findChange() to calculate whether the person is accelerating (spinning).
      findChange();
    }
  }
}

//calculate the change in z acceleration
void findChange() 
{
  float b = accel.cz; //new z accel
  float diff = a-b; //find the difference in accelerations

    if (abs(diff) > 0.1){
       Serial.print("move");
       for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {
          left_strip.setPixelColor(i, max_brightness, 0, 0, 0);
        }
        for (int i=0; i < RIGHT_STRIP_NUM_LEDS; i++) {
           right_strip.setPixelColor(i, max_brightness, 0, 0, 0);
        }
        left_strip.show();
        right_strip.show();
        delay(500);
    }
      if(millis() - lastMove > checkTime){ //check to see how much time has passed
        a = accel.cz; //reset the idle acceleration
      }
      for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {
            left_strip.setPixelColor(i, 0, max_brightness, 0, 0);
          }
          for (int i=0; i < RIGHT_STRIP_NUM_LEDS; i++) {
             right_strip.setPixelColor(i, 0, max_brightness, 0, 0);
          }

      left_strip.show();
      right_strip.show();

      Serial.println();
}
