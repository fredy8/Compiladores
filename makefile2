IDIR =./include
CC=clang++
CFLAGS=-I$(IDIR) -std=c++11

BDIR=./bin
ODIR=./obj
SDIR=./src

_DEPS = $(shell find $(IDIR) -type f)
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = $(shell find $(SDIR) -type f -name '*.cc')
OBJ = $(patsubst $(SDIR)/%.cc, $(ODIR)/%.o, $(_OBJ))

main: obj/main.o $(OBJ)
		$(CC) -o $(BDIR)/$@ $^ $(CFLAGS)

obj/main.o: $(SDIR)/main.cpp
		$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
		rm -f $(BDIR)/* *~ core $(INCDIR)/*~ 
		find obj -type f -name '*.o' -exec rm {} +

