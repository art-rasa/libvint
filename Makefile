CC=gcc
CFLAGS=-g --pedantic -I.
DEPS = libvint.h
_OBJ = main.o libvint.o 
ODIR=build

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main: $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~  
