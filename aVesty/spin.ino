#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;

float a;
void spin_setup()
{
  a = accel.cz; //initialze to the z accel
}

// The loop function will simply check for new data from the
//  accelerometer and print it out if it's available.

void spin()
{
   accel.init(SCALE_2G, ODR_100); //data collection rate and acceleration scale
   
    while(checkButtons){ //unsure if this is in the right place
      if (accel.available()){
      // First, use accel.read() to read the new variables:
      accel.read();
      findChange();

      left_strip.show();
      right_strip.show();
    }
  }
}




//calculate the change in y acceleration
void findChange() 
{
  float b = accel.cz; //new z accel
  float diff = a-b;
  
//  Serial.print(a);
//  Serial.print("\t");
//  Serial.print(b)
//  Serial.print("\t");
//  Serial.print("diff " + diff);

  
    if (diff > 0.2){
       Serial.print("clockwise");
       for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {
          left_strip.setPixelColor(i, max_brightness, 0, 0, 0);
        }
        for (int i=0; i < RIGHT_STRIP_NUM_LEDS; i++) {
           right_strip.setPixelColor(i, max_brightness, 0, 0, 0);
        }
       delay(2000); 
    }
    if (diff < -0.2){
       Serial.print("counterclockwise");
       for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {
          left_strip.setPixelColor(i, max_brightness, 0, 0, 0);
        }
        for (int i=0; i < RIGHT_STRIP_NUM_LEDS; i++) {
           right_strip.setPixelColor(i, max_brightness, 0, 0, 0);
        }
       delay(2000);
    }
    else{
      Serial.print("idle");
      a = accel.cz; //reset the idle acceleration
      for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {
            left_strip.setPixelColor(i, 0, max_brightness, 0, 0);
          }
          for (int i=0; i < RIGHT_STRIP_NUM_LEDS; i++) {
             right_strip.setPixelColor(i, 0, max_brightness, 0, 0);
          }
      }

      Serial.println();
    
}
