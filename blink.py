#soure: https://www.raspinews.com/blinking-led-on-raspberry-pi-using-python/ 
#press Ctrl + C to terminate the program
import RPi.GPIO as GPIO
import time

LedPin = 8    # pin11

def setup():
  GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
  GPIO.setup(LedPin, GPIO.OUT)   # Set LedPin's mode is output
  GPIO.output(LedPin, GPIO.HIGH) # Set LedPin high(+3.3V) to turn on led

def blink():
  while True:
    GPIO.output(LedPin, GPIO.HIGH)  # led on
    time.sleep(1)
    print("on")
    GPIO.output(LedPin, GPIO.LOW) # led off
    time.sleep(1)
    print("off")

def destroy():
  GPIO.output(LedPin, GPIO.LOW)   # led off
  GPIO.cleanup()                  # Release resource

if __name__ == '__main__':     # Program start from here
  setup()
  try:
    blink()
  except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
    destroy()
