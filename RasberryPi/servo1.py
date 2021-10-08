# Simple demo of of the PCA9685 PWM servo/LED controller library.
# This will move channel 0 from min to max position repeatedly.
# Author: Tony DiCola
# License: Public Domain
'''from __future__ import division
import time

# Import the PCA9685 module.
import Adafruit_PCA9685'''


# Uncomment to enable debug output.
#import logging
#logging.basicConfig(level=logging.DEBUG)

# Initialise the PCA9685 using the default address (0x40).
'''pwm = Adafruit_PCA9685.PCA9685()'''

# Alternatively specify a different address and/or bus:
#pwm = Adafruit_PCA9685.PCA9685(address=0x41, busnum=2)

''' 1) MIN MAX FOR ALL MOTORS'''
# Configure min and max servo pulse lengths
servo_min = 150  # Min pulse length out of 4096
servo_max = 600  # Max pulse length out of 4096

# Helper function to make setting a servo pulse width simpler.
def set_servo_pulse(channel, pulse):
    pulse_length = 1000000    # 1,000,000 us per second
    pulse_length //= 60       # 60 Hz
    print('{0}us per period'.format(pulse_length))
    pulse_length //= 4096     # 12 bits of resolution
    print('{0}us per bit'.format(pulse_length))
    pulse *= 1000
    pulse //= pulse_length
    '''pwm.set_pwm(channel, 0, pulse)'''


'''# Set frequency to 60hz, good for servos.
pwm.set_pwm_freq(60)'''

def moveServo(channel, on, off):
    pwm.set_pwm(channel, on, off)
    time.sleep(1) #CHANGE?
    pwm.set_pwm(channel, on, off)
    time.sleep(1)

def map(x, in_min, in_max, out_min, out_max): #works for negative as well
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

def angle2Pulse(angle):
    return map(angle, 0, 180, servo_min, servo_max)

def pulse2Angle(pulse):
    return map(pulse,servo_min, servo_max, 0, 180)

#not super accurate, 2-3 pulse values are grouped into 1 angle
for i in range(150, 601):
    print( 'pulse', i)
    print( 'angle', pulse2Angle(i))

'''
    


1) map distance range 
2) translate EMG data to either pulse or angle

we can test the motors with the hand get max, min movement, then we have
an equation for the distance movement per angle (would be just horizontal)

pythagorean?
'''


