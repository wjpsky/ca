#######################################################################
# Makefile for inclusion by other projects
#   heavily copied from original libarduino sources
#   (c) 2009, for all changes belong to Henrik Sandklef
#	which lead to the current version
#	(c) 2011, for all changes belong to Petre Mihail Anton
#######################################################################

CC=avr-gcc

MKDIR=$(CURDIR)/Make-dir

LIBFLAGS = -c -g -Os -ffunction-sections -fdata-sections -mmcu=$(CPU) -DF_CPU=$(F_CPU) -DARDUINO=22 -I$(MKDIR)

CFLAGS=	$(LIBFLAGS) -Wall -Wstrict-prototypes -Wa,-ahlms=$(PROG).lst -fno-exceptions \
		 -DENABLE_PWM -L$(MKDIR) -lcore

LDFLAGS=-Wl,-Map=$(PROG).map,--cref -mmcu=$(CPU) -L$(MKDIR) -lcore -lm

AVRDUDE_DUE=avrdude -p m328p -P $(DUE_USB_DEV) -c stk500v1 -b 57600 -F -u -U flash:w:$(PROG).rom
AVRDUDE_UNO=avrdude -p atmega328p -P $(UNO_USB_DEV) -cstk500v1 -b 115200 -F -u -U flash:w:$(PROG).rom
AVRDUDE_2560=avrdude -p atmega2560 -P $(2560_USB_DEV) -c stk500v2 -b 115200 -F -u -U flash:w:$(PROG).rom

OBJ = $(SRC:.c=.o)

# build the library
lib:
	@ cp $(ARD_PATH)/* $(MKDIR)
	@ cd $(MKDIR) && \
	rm -f main.cpp main.cxx README.Makefile && \
	$(CC) -w $(LIBFLAGS) *.c && \
	avr-g++ -w $(LIBFLAGS) *.cpp && \
	avr-ar rcs libcore.a *.o
	@ echo "Arduino core lib generated"

# compile .c into .o
%.o: %.c lib
	$(CC) $(CFLAGS) $*.c

$(PROG): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROG).x
	@ $(MAKE) clean-lib --silent
	@ echo "Test passed"
	
$(PROG).elf: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROG).elf

$(PROG).rom: $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom
	$(MKDIR)/checksize $(PROG).elf

install: $(PROG).rom 
	# SparkFun pocket ISP programmer
	# atmega328 based Uno / Duemilanove
	$(AVRDUDE)

all: install

clean-lib:
	@ cd $(MKDIR) && rm -f *.o *.c *.cpp *.Makefile *.h *.a

clean: clean-lib
	@ -rm -f *.o *.rom *.elf *.map *~ *.lst *.x
	@ echo "Project cleaned"

# reprogram the fuses for the right clock source
fuse:
	avrdude -p atmega168 -c stk200 -U lfuse:w:0x62:m
