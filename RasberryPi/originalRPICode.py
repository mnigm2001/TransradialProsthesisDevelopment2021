
# Simple demo of of the PCA9685 PWM servo/LED controller library.
# This will move channel 0 from min to max position repeatedly.
# Author: Tony DiCola
# License: Public Domain
from __future__ import division
import time

# Import the PCA9685 module.
import Adafruit_PCA9685
#import home/pi/Adafruit_PCA9685
#import /home/pi/Adafruit_Python_PCA9685/Adafruit_PCA9685/PCA9685.py

# Uncomment to enable debug output.
#import logging
#logging.basicConfig(level=logging.DEBUG)

# Initialise the PCA9685 using the default address (0x40).
pwm = Adafruit_PCA9685.PCA9685()

# Alternatively specify a different address and/or bus:
#pwm = Adafruit_PCA9685.PCA9685(address=0x41, busnum=2)

# Configure min and max servo pulse lengths
servo_min = 150  
servo_max = 600  


# Helper function to make setting a servo pulse width simpler.
def set_servo_pulse(channel, pulse):
    pulse_length = 1000000    # 1,000,000 us per second
    pulse_length //= 60       # 60 Hz
    print('{0}us per period'.format(pulse_length))
    pulse_length //= 4096     # 12 bits of resolution
    print('{0}us per bit'.format(pulse_length))
    pulse *= 1000
    pulse //= pulse_length
    pwm.set_pwm(channel, 0, pulse)

# Set frequency to 60hz, good for servos.
pwm.set_pwm_freq(50)

# Move a specified servo from input on to off
def moveServo(channel, on, off):
    pwm.set_pwm(channel, 0, on)
    time.sleep(1) #CHANGE?
    pwm.set_pwm(channel, 0, off)
    time.sleep(1)

# Map 1 input range into another range with different values
def map(x, in_min, in_max, out_min, out_max): #works for negative as well
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

# Maps the input angle value into a pulse value
def angle2Pulse(angle):
    return map(angle, 0, 180, servo_min, servo_max)

# Maps the input pulse value into an angle value
def pulse2Angle(pulse):
    return map(pulse,servo_min, servo_max, 0, 180)

def main():
    while True:
        moveServo(15,servo_min,servo_max)
        moveServo(14,servo_min,servo_max)
        moveServo(12,servo_min,servo_max)
        moveServo(13,servo_min,servo_max)
        moveServo(4,servo_min,servo_max)

