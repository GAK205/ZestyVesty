/******************************************************************************
MMA8452Q_Basic.ino
SFE_MMA8452Q Library Basic Example Sketch
Jim Lindblom @ SparkFun Electronics
Original Creation Date: June 3, 2014
https://github.com/sparkfun/MMA8452_Accelerometer

This sketch uses the SparkFun_MMA8452Q library to initialize the
accelerometer, and stream values from it.

Hardware hookup:
  Arduino --------------- MMA8452Q Breakout
    3.3V  ---------------     3.3V
    GND   ---------------     GND
  SDA (A4) --\/330 Ohm\/--    SDA
  SCL (A5) --\/330 Ohm\/--    SCL

The MMA8452Q is a 3.3V max sensor, so you'll need to do some 
level-shifting between the Arduino and the breakout. Series
resistors on the SDA and SCL lines should do the trick.

Development environment specifics:
	IDE: Arduino 1.0.5
	Hardware Platform: Arduino Uno
	
	**Updated for Arduino 1.6.4 5/2015**

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/
#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;
int LEDpin1 = 7; //red
int LEDpin2 = 6; //blue
int LEDgreen = 5; //yellow/green light
enum State{
  idle,
  right,
  left  
};

// The setup function simply starts serial and initializes the
//  accelerometer.
State curState;

double avgAccel;

void setup()
{
  Serial.begin(9600);
  Serial.println("MMA8452Q Test Code!");
  
  pinMode(LEDpin1,OUTPUT); //red
  pinMode(LEDpin2,OUTPUT); //blue
  pinMode(LEDgreen,OUTPUT); //yellow
//
  curState = idle;

  avgAccel = 0;
  
  accel.init(SCALE_2G, ODR_100);
}

// The loop function will simply check for new data from the
//  accelerometer and print it out if it's available.
void loop()
{
 // digitalWrite(LEDpin1,HIGH); //turns on the led
  //digitalWrite(LEDpin2,HIGH); //turns on the led
   
  // Use the accel.available() function to wait for new data
  //  from the accelerometer.
  if (accel.available())
  {
    //Serial.println("avail");
    // First, use accel.read() to read the new variables:
    accel.read();
    
    
    findChange();
    //Serial.println(); // Print new line every time.

  }
}

// The function demonstrates how to use the accel.x, accel.y and
//  accel.z variables.
// Before using these variables you must call the accel.read()
//  function!
void printAccels()
{
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.y, 3);
  Serial.print("\t");
  Serial.print(accel.z, 3);
  Serial.print("\t");
}

//set up the LEDs
//void rb_setRed(uint8_t max_brightness) 
//{
//  for (int i=0; i < LEFT_STRIP_NUM_LEDS/2; i++) {
//  left_strip.setPixelColor(i, max_brightness, 0, 0, 0);
//  }
//}
//setPixelColor(I, red, green, blue, white);

//calculate the change in y acceleration
void findChange() 
{
  double xAccel = accel.cy;
//  //double zAccel = accel.cz;
  delay(10);
  accel.read();
  double newXaccel = accel.cx;
  //double avgAccel = (avgAccel + newXaccel)/2;
//   digitalWrite(LEDgreen,HIGH); //turns on the leD
//  digitalWrite(LEDpin1,HIGH); //turns on the led
//  digitalWrite(LEDpin2,HIGH); //turns on the led

  //have it go red or blue until you stop spinnng
  //it resets
  //then you can test again
  
      Serial.print(newXaccel, 3); 
      Serial.print("\t");
      Serial.print(avgAccel, 3); 
      Serial.println(); 
 
    if (newXaccel > 0.1){
       digitalWrite(LEDpin1,LOW); //turns off the led
       digitalWrite(LEDgreen,LOW);
       digitalWrite(LEDpin2,HIGH); //turns on the led
       delay(1000);
    }
    if (newXaccel < -0.1){
       digitalWrite(LEDpin2,LOW); //turns off the led
       digitalWrite(LEDgreen,LOW);
        digitalWrite(LEDpin1,HIGH); //turns on the led
        delay(1000);
    }
    else{
      digitalWrite(LEDpin1,LOW); //turns off the led
      digitalWrite(LEDpin2,LOW); //turns on the led
      digitalWrite(LEDgreen,HIGH);
    }


//switch(curState){
//  case idle:
//    //delay(1000); 
//    if (newXaccel < -0.07 ){
//      curState = right;
//    }
//    else if (newXaccel > 0.07){
//      curState = left;
//    }
//    else{
//      curState = idle;
//    }
//    digitalWrite(LEDpin1,LOW); //turns off the led
//    digitalWrite(LEDpin2,LOW); //turns on the led
//    digitalWrite(LEDgreen,HIGH);
//
//    break;
//    
//  case left:
//    //delay(1000);
//     digitalWrite(LEDpin1,LOW); //turns off the led
//     digitalWrite(LEDgreen,LOW);
//     digitalWrite(LEDpin2,HIGH); //turns on the led
//     if (newXaccel < 0.07){
//      curState = idle;
//     }
//     break;
//   
//  case right: //RED
//        //delay(1000);
//       digitalWrite(LEDpin2,LOW); //turns off the led
//       digitalWrite(LEDgreen,LOW);
//       digitalWrite(LEDpin1,HIGH); //turns on the led
//       if (newXaccel > -0.07){
//          curState = idle;
//       }
//       break;
//}
  
}
  
  

// This function demonstrates how to use the accel.cx, accel.cy,
//  and accel.cz variables.
// Before using these variables you must call the accel.read()
//  function!
void printCalculatedAccels()
{ 
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.cz, 3);
  Serial.print("\t");
}


// This function demonstrates how to use the accel.readPL()
// function, which reads the portrait/landscape status of the
// sensor.
void printOrientation()
{
  //accel.readPL() will return a byte containing information
  // about the orientation of the sensor. It will be either
  // PORTRAIT_U, PORTRAIT_D, LANDSCAPE_R, LANDSCAPE_L, or
  // LOCKOUT.
  byte pl = accel.readPL();
  switch (pl)
  {
  case PORTRAIT_U:
    Serial.print("Portrait Up");
    Serial.print("\t");
    Serial.print(accel.cy, 3);
    break;
  case PORTRAIT_D:
    Serial.print("Portrait Down");
    Serial.print("\t");
    Serial.print(accel.cy, 3);
    break;
  case LANDSCAPE_R:
    Serial.print("Landscape Right");
    break;
  case LANDSCAPE_L:
    Serial.print("Landscape Left");
    break;
  case LOCKOUT:
    Serial.print("Flat");
    break;
  }
}
