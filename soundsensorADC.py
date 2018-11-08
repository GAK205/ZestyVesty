
import spidev
import time
import os

 spi = spidev.SpiDev()
    spi.open(0,0)
    spi.max_speed_hz = 1000000

def read (adc_channel=0,spi_channel=0):
    adc = spi.xfer2([1, (8+channel)<<4, 0])
    data =((adc[1]&3)<< 8) + adc[2]
    return data 
   
    