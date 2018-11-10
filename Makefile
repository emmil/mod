CC=gcc
SRC=src/
CFLAGS=-O2 -g -fomit-frame-pointer -Wall
OBJ= $(SRC)ade32.o $(SRC)decode.o $(SRC)sample.o
DEST=mod

all: $(DEST)

$(DEST): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(DEST)

$(OBJ): $(SRC)mod.h $(SRC)ade32.h $(SRC)ade32tbl.h $(SRC)version.h $(SRC)decode.h

clean:
	rm -f $(SRC)*.o

cleanall:
	rm -f $(SRC)*.o $(DEST)
