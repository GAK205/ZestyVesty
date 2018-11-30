#include "arduinoFFT.h"
 
#define SAMPLES 32             //Must be a power of 2
#define SAMPLING_FREQUENCY 8000 //Hz, must be less than 10000 due to ADC


arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];
 
void fft_setup() {
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}
 
void light_FFT() {
  
   float levels[16];
   
   for (int i=0; i<16; i++) levels[i] = 0; // initialize levels to 0

   
   while(checkButtons()){
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

      
      double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
      /*PRINT RESULTS*/
  //    Serial.println(peak);     //Print out what frequency is the most dominant.

      for(int i=1; i<(SAMPLES/2); i++)
      {
        levels[i] = ( vReal[2*i] + levels[i]) / 2;
      }

        /*Serial.printf("%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", \
      levels[0], levels[1], levels[2], levels[3], levels[4], levels[5], \
      levels[6], levels[7], levels[8], levels[9], levels[10], levels[11], \
      levels[12], levels[13], levels[14], levels[15]);*/
//  
//      float average = 0;
//      float sum = 0;
//      /*find Average*/
//      for(int i=0; i<(SAMPLES/2); i++)
//      {
//        
//        if(((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES) > 63){
//          sum += vReal[i];
//        }
//      }
// 
//  
//  //    average = sum / (SAMPLES/2);
//      average = 4;
//      
//      bool isOn[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
  
//    /*Light significant data*/
//    for(int i=0; i<(SAMPLES/2); i++)
//    {
//      if(exists((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES)){
//        sum += vReal[i];
//        Serial.print(0);
//        Serial.print(" ");
//        Serial.print(average);
//        Serial.print(" ");
//        Serial.println(vReal[i], 1);
//
////        //LED on or off
////        if(vReal[i] > average){
////          isOn[i] = 1;
////        }
////        else{
////          isOn[i] = 0;
////        }
//        
//      }
//    }
  
//    /*Turn on lights*/
//    for (int i=0; i < 4; i++) {
//
//      //light only if amplitude greater than average
//      if(isOn[i]){
//        left_strip.setPixelColor(i, (SA_COLOR_STEP*i + 255), (255 - SA_COLOR_STEP*i),0, 0);
//      }
//    }
//    left_strip.show();
//    

//    /*Print all data*/
//    for(int i=0; i<(SAMPLES/2); i++)
//    {
//      if(((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES) > 63){
//        sum += vReal[i];
//        Serial.print(0);
//        Serial.print(" ");
//        Serial.print(average);
//        Serial.print(" ");
//        Serial.println(vReal[i], 1);
//      }
//      
//    }
   
//      for(int i=1; i<(SAMPLES/2); i++)
//      {
//          /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
//            Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
//            Serial.print(">> ");
//  //           View only this line in serial plotter to visualize the bins
//            Serial.println(vReal[i], 1);
//      }
      
//      Serial.println("=================="); 

  //    delay(1000);  //Repeat the process every second OR:
  //    while(1);       //Run code once
  
  }
}

//bool exists(double val) {
//  bool a = false;
//  int key[] = {375, 625, 875, 1000, 1250, 1375, 1625, 1875, 2000, 2375, 2813, 3000, 3250};
//  for (int i = 0; i < 13; i++){
//    if (val == key[i]){
//      a = true;
//    }
//  }
//return true;
//}
