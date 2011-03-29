BIN=func
OBJS= collision_logic.c
DISTFILE_TAR=handin.tar
DISTFILE_TARGZ=handin.tar.gz

$(BIN): $(OBJS)

clean:
	rm -f $(BIN)  $(DISTFILE_TAR)  $(DISTFILE_TARGZ)  

dist: $(BIN)
	rm -f  $(DISTFILE_TAR)  $(DISTFILE_TARGZ) 

	tar cvf $(DISTFILE_TAR) *.c  $(BIN) Makefile
	gzip $(DISTFILE_TAR)

$(BIN): $(OBJS) 
	gcc $(OBJS) -o $(BIN)
