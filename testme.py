import os

#os.system('cd /home/pi/rpi-rgb-led-matrix/bindings/python/samples')
#os.system("ls -ltra")
os.system('sudo python3 /home/pi/rpi-rgb-led-matrix/bindings/python/samples/rotating-block-generator.py --led-slowdown-gpio=2 --led-rows=32 --led-cols=64 --led-brightness=30')

print("testing")
