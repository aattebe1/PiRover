CC=gcc

SDIR=src
IDIR=include
ODIR=obj

LIBS=-lwiringPi -lpthread

CFLAGS=-I$(IDIR)

_DEPS=Pins.h PiRover.h LCM1602.h L298.h HCSR04.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_SOURCES=PiRover.c Pins.c LCM1602.c L298.c HCSR04.c
SOURCES=$(patsubst %,$(SDIR)/%,$(_SOURCES))

_OBJ=PiRover.o Pins.o LCM1602.o L298.o HCSR04.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

PiRover: $(OBJ)
	$(CC) -o PiRover $(SOURCES) $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
