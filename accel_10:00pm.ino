#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;

bool checkButtons = true;

float a;
float base;
//float sum;
//int counter;
//float average;

void spin_setup()
{
}

void spin()
{
   accel.init(SCALE_2G, ODR_100); //data collection rate and acceleration scale
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
  float b = accel.cz; //read in current acceleration
  float diff = a-b; //calculate difference
  float buff = 0.05; //reasonable buffer given values

  
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(diff);
  Serial.print("\t");
  Serial.print(base);
  Serial.print("\t");

  //clockwise
  if (diff > 0.15){
     Serial.print("clockwise");
     
     bool stopped = true;
     while (stopped){ //until acceleration has normalized, continue to show color on led
      accel.read();
       float c = accel.cz;
       if (c < base + buff){ 
          stopped = false;
          }
        }
      a = accel.cz;
      //delay(1000); 
   }

  //counterclockwise
  if (diff < -0.15){
     Serial.print("counterclockwise");
     
     bool stopped = true;
     while (stopped){ //until acceleration has normalized, continue to show color on led
       float c = accel.cz;
       
       if (c > base + buff){
          stopped = false;
          }
        }
      a = accel.cz;
      //delay(1000);
    }

  //idle
  else{
     Serial.print("idle");
     
//     sum+=b;
//     counter++;
//     average = sum / counter;
//     Serial.print(average);
     
     a = accel.cz; //reset the idle acceleration

    }
  Serial.println();

}
