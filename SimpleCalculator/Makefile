
# makefile SimpleCalculator

HEADERS = sum.h mult.h div.h
OBJS = main.o sum.o mult.o div.o
CFLAGS = -g -Wall -v -o
BINARY = SimpleCalculator

all: $(BINARY)

$(BINARY):$(OBJS)
	gcc $(CFLAGS) $@ $(OBJS)

main.o: main.c $(HEADERS)

sum.o: sum.c sum.h

mult.o: mult.c mult.h

div.o: div.c div.h


PHONY: clean

clean:
	rm -f *.o $(BINARY)