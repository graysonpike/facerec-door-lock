# For Python 2.7

# Python script to control the servo
# There aren't any libraries to control PWM GPIO output in C/C++,
# so this script is being used temporarily until I can write a C++ class for it

import sys
import os
import time
import wiringpi


DELAY_PERIOD = 0.01


'''
	Initializes a given PWM GPIO pin for output
'''
def init(pin):

	# Use GPIO naming
	wiringpi.wiringPiSetupGpio()

	# Set mode for pin 18 to PWM
	wiringpi.pinMode(pin, wiringpi.GPIO.PWM_OUTPUT)

	# Set mode of PWM to milliseconds
	wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)

	# Set clock
	wiringpi.pwmSetClock(192)
	wiringpi.pwmSetRange(2000)


'''
	Outputs a given pin on 
'''
def main():

	# Ensure that sudo permissions are enabled to prevent kernel crash
	if(os.getuid() != 0):
		print("Error: This program must be run as root.")
		print("Correct usage: sudo python servo.py <pulse_time>")
		print("    where <pulse_time> is in milliseconds")
		exit()

	# Ensure there are the correct number of arguments
	if(len(sys.argv) != 2):
		print("Error: Incorrect syntax.")
		print("Correct usage: sudo python servo.py <pulse_time>")
		print("    where <pulse_time> is in milliseconds")
		exit()

	# Init pin 18 for output
	init(18)

	# Output the given value to the servo
	wiringpi.pwmWrite(18, int(sys.argv[1]))

main()