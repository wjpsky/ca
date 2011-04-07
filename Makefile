BIN= prog
OBJS= collision_logic.c object_calculations.c collision_main.c collisionInterface.c \
 collision_sensor.c


$(BIN): $(OBJS)

clean:
	rm -f $(BIN)

dist: $(BIN)
	rm -f  $(DISTFILE_TAR)  $(DISTFILE_TARGZ) 

	tar cvf $(DISTFILE_TAR) *.c  $(BIN) Makefile
	gzip $(DISTFILE_TAR)


$(BIN): $(OBJS) 
	gcc $(OBJS) -Wall -fprofile-arcs -ftest-coverage  -o $(BIN)


