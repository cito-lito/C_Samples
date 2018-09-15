
OBJS = main.o sieve.o
CFLAGS = -Wall
BINARY = Eratosthenes

all: $(BINARY)
        
$(BINARY): $(OBJS)
	gcc -g $(CFLAGS) -o $@ $(OBJS)

main.o: main.c sieve.h

sieve.o: sieve.c sieve.h


.PHONY: clean

clean: 
	rm -f $(BINARY) *.o
