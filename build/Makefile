IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = main.o calculator_t.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: calculator

$(ODIR)/main.o: $(ODIR)/main.cpp $(ODIR)/calculator_t.cpp $(IDIR)/chain_t.hpp $(IDIR)/language_t.hpp $(IDIR)/calculator_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

calculator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
