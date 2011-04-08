# #######################################################################
# Makefile for inclusion by other projects
#   heavily copied from original libarduino sources
#   (c) 2009, for all changes belong to Henrik Sandklef
#	which lead to the current version
#	(c) 2011, for all changes belong to Petre Mihail Anton
#######################################################################

# adapt to your project
PROG=comp
SRC=$(PROG).c

#     Change device names to corespond to your system
#  Description
#  =============
#    DUE_USB_DEV - used for Arduino DueMillaNove
#    UNO_USB_DEV - used for Arduino Uno
#
# here are various USB device names for various operating system and Arduinos:
# if you're using GNU/Linux (Ubuntu/Debian/Fedora.....):
#	DUE_USB_DEV=/dev/ttyUSB0
#	UNO_USB_DEV=/dev/ttyACM0
# if you're using Mac:
#	DUE_USB_DEV=
#	UNO_USB_DEV=/dev/tty.usbmodemfa141 (check name!)
# Hint:
#    Launch the Arduino program to see what your USB device 
#    is called (look under the port settings)
                                                                                  
DUE_USB_DEV=/dev/ttyUSB0
UNO_USB_DEV=/dev/ttyACM0
2560_USB_DEV=/dev/ttyACM0

# modify if the libarduino directory is different than what's below

LIBARDUINO_PATH=/opt/libarduino

# change device names to corespond to your Arduino board
# if you're using the UNO:
#   AVRDUDE=$(AVRDUDE_UNO)
# if you're using the DUE:
#   AVRDUDE=$(AVRDUDE_DUE)
#	AVRDUDE_2560

AVRDUDE=$(AVRDUDE_UNO)

# please uncomment the CPU that is used on your arduino
CPU=atmega328p
#CPU=atmega168
#CPU=atmega2560

# please uncomment the speed that corresponds to your arduino (normally 16MHz)
F_CPU=16000000
#F_CPU=8000000

#change to Arduino installation path (should contain among many others WProgram.h)
# if you're using Ubuntu:
#   ARD_PATH=/usr/share/arduino/hardware/arduino/cores/arduino
# if you're using Mac:
#	ARD_PATH=
ARD_PATH=/usr/share/arduino/hardware/arduino/cores/arduino

#do not change this
include $(CURDIR)/Make-dir/arduino.mk

