
#source: https://www.instructables.com/id/Raspberry-Pi-Home-Automation-Control-lights-comput/
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

GPIO.setmode(GPIO.BCM
GPIO.setup(2, GPIO.OUT)
GPIO.output(2, False)
