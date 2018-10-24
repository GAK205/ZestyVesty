#!/usr/bin/env python
# Display a runtext with double-buffering.
from samplebase import SampleBase
from rgbmatrix import graphics



class RunText(SampleBase):
    def __init__(self, *args, **kwargs):
        super(RunText, self).__init__(*args, **kwargs)
        self.parser.add_argument("-t", "--text", help="The text to scroll on the RGB LED panel", default="ESE 205 is Fun")

    def run(self):
        offscreen_canvas = self.matrix.CreateFrameCanvas()
        font = graphics.Font()
        font.LoadFont(".GPIO.setmode(GPIO.BCM)./../../fonts/7x13.bdf")
        textColor = graphics.Color(205, 240, 0)
        pos = offscreen_canvas.width
        my_text = self.args.text

        while True:
            offscreen_canvas.Clear()
            len = graphics.DrawText(offscreen_canvas, font, pos, 10, textColor, my_text)
            pos -= 1
            if (pos + len < 0):
                pos = offscreen_canvas.width

            time.sleep(0.05)
            offscreen_canvas = self.matrix.SwapOnVSync(offscreen_canvas)
from time import sleep

    import RPi.GPIO as GPIO
    import time
    
    #chosed SPI pin
    SPICLK = 16 #board 36
    # freely chosen SPI pins
    SPICLK = 16  # BOARD 36
    SPIMISO = 19  # BOARD 35
    SPIMOSI = 20  # BOARD 38
    SPICS = 25  # BOARD 22
     
    # set up the SPI interface pins
    GPIO.setup([SPIMOSI, SPICLK, SPICS], GPIO.OUT)
    GPIO.setup(SPIMISO, GPIO.IN)
    
    # 10k trim pot connected to adc #0
    potentiometer_adc = 0;

# Main function
if __name__ == "__main__":
    
        
     
   

    
    
    ##need to read info from potentiometer circuit, and then set the text to represent that data
    
    run_text = RunText()
    if (not run_text.process()):
        run_text.print_help()
