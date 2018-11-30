#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;

#define SPIN_THRESHOLD 0.3


float a;
float base;
//float sum;
//int counter;
//float average;

void spin_setup()
{
  base = 0;
}

void spin()
{
  accel.init(SCALE_2G, ODR_100); //data collection rate and acceleration scale

  delay(4000);
   a = accel.cz; //initialze to the z accel

   base = a;
   
//   counter = 0;
//   sum = 0;
   
    while(checkButtons){ //unsure if this is in the right place
      if (accel.available()){
    
      // First, use accel.read() to read the new variables:
      accel.read();
      
      findChange();
    }
  }
}

//calculate the change in y acceleration
void findChange() 
{
  float a = accel.cz; //read in current acceleration

  
  Serial.print("Base:   ");
  Serial.print(base);
  Serial.print("\t");
  Serial.print("new:  .");
  Serial.print(a);

  //clockwise
  if (a > (base + SPIN_THRESHOLD)){
     Serial.print("clockwise");
      //delay(1000); 
   }
  //counterclockwise
  else if (a < (base - SPIN_THRESHOLD)){
     Serial.print("counterclockwise");
     
     //delay(1000);
  }
  //idle 
  else{
     Serial.print("idle");
  }
  Serial.println();
}
