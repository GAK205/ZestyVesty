#include "arduinoFFT.h"
 
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 8000 //Hz, must be less than 10000 due to ADC


arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];

float peakMax = 0;
 
void fft_setup() {
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}
 
void light_FFT() {
  
   float levels[SAMPLES/4];
   
   for (int i=0; i< (SAMPLES/4); i++)
   { 
      levels[i] = 0; // initialize levels to 0

//      Serial.print("Level ");
//      Serial.print(i);
//      Serial.print(": ");
//      Serial.println(levels[i]);
   }
   
   while(checkButtons()){
      //reset max for new sample set
//       peakMax = 0;
      
      /*SAMPLING*/
      for(int i=0; i<SAMPLES; i++)
      {
          microseconds = micros();    //Overflows after around 70 minutes!
       
          vReal[i] = analogRead(1);
          vImag[i] = 0;
       
          while(micros() < (microseconds + sampling_period_us)){
          }
      }
      
      /*FFT*/
      FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
      FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
      
//      double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
      /*PRINT RESULTS*/
//      Serial.println(peak);     //Print out what frequency is the most dominant.


//      Serial.println(peakMax);
      Serial.println("..... ");
        
      for(int i = 1; i<(SAMPLES/4); i++)
      {
        levels[i] = ( vReal[4*i] + levels[i]) / 2;
        
//        Serial.print("Level ");
//        Serial.print(i);
//        Serial.print(": ");
//        Serial.println(levels[i]);
        if(levels[i] > peakMax){
          peakMax = levels[i];
        } 
      }

    float ratio = 0;
    int brightness = 1;
    /*Turn on lights*/
    for (int i=0; i < LEFT_STRIP_NUM_LEDS; i++) {

      //calculate light ratio
      ratio = levels[i]/peakMax;

      brightness = ratio*max_brightness;
    
//      Serial.print("brightness");
//      Serial.print(i);
//      Serial.print(": ");
//      Serial.println(brightness);


      left_strip.setPixelColor(i, 0, 0, ratio*max_brightness, 0);
      right_strip.setPixelColor(i, 0, 0, ratio*max_brightness, 0);
      
      //gradient lighting
//      left_strip.setPixelColor(i, (SA_COLOR_STEP*i + 255), (255 - SA_COLOR_STEP*i),0, 0);
    
    }
    
//    Serial.println("==================");

    left_strip.show();
    right_strip.show();
  }
}
