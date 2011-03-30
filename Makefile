BIN= prog
OBJS= collision_logic.c


$(BIN): $(OBJS)

clean:
	rm -f $(BIN)

dist: $(BIN)
	rm -f  $(DISTFILE_TAR)  $(DISTFILE_TARGZ) 

	tar cvf $(DISTFILE_TAR) *.c  $(BIN) Makefile
	gzip $(DISTFILE_TAR)

$(BIN): $(OBJS) 
	gcc $(OBJS) -o $(BIN)
