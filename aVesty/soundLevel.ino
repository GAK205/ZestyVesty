const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

int numSound;
 
void soundLevel_setup() 
{
   Serial.begin(115200);

   numSound = 0;
}
 
 
void soundLevel() 
{
  while(checkButtons()){
    
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(1);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
 
   //number of led lights to light up out of 10 for both front and back
   numSound = ((int)(volts*10) + numSound)/2;

   //cap at 10 LEDs
   if(numSound > 11){
      numSound = 11;
   }

//   Serial.println(numSound);

    clearStrips();
    
    for (int i=0; i < numSound; i++) {
        left_strip.setPixelColor(i, (SA_COLOR_STEP*i + 255), (255 - SA_COLOR_STEP*i),0, 0);
        right_strip.setPixelColor(i, (SA_COLOR_STEP*i + 255), (255 - SA_COLOR_STEP*i),0, 0);
    }
    for (int k= LEFT_STRIP_NUM_LEDS; k > (LEFT_STRIP_NUM_LEDS - numSound); k--) {
        left_strip.setPixelColor(k, (255 - SA_COLOR_STEP*(k-12)), (SA_COLOR_STEP*(k-12)),0, 0);
        right_strip.setPixelColor(k, (255 - SA_COLOR_STEP*(k-12)), (SA_COLOR_STEP*(k-12)),0, 0);
    }

    
    left_strip.show();
    right_strip.show();
  }
}
