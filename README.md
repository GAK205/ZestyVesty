ZestyVesty, ESE 205

Members: Kenneth McNelly, Gillian Laming, Andre Cook 

Our work:
- all code can be found inside the folder aVesty
- other files are files we used along the way to our final project.

Light_FFT.ino
Implements arduinoFFT
	-by kosmos	Github: https://github.com/kosme/arduinoFFT

	Displays an FFT pattern across the light strips. Each light indicating a significant frequency and the brightness of the light demonstrates the ranking of intensity of the frequency after the FFT, with the most significant frequency being the brightest.


Rainbow.ino – referenced from John McNelly's LED Trumpet project

	Displays a flashing animated rainbow pattern.


red_blue.ino – referenced from John McNelly's LED Trumpet project
	
	Imitates flashing police lights


soundLevel.ino
https://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels

	Measures the volume level from the sound sensor with a correlating voltage output.
	Then using the voltage as a ratio, a number of lights light up accordingly.
	

spin.ino
Implements SparkFun's MMA8452Q accelerometer library
	-Uses example code in order to read and interpret the sensor data.
	-Using the acceleration data, the vest lights corresponding to movement.