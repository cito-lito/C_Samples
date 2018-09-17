
OBJS = newton_main.o newton.o
BINARY = newton
CFLAGS = -Wall 

all: $(BINARY)

$(BINARY): $(OBJS)
	gcc -g  $(CFLAGS) -o $@ $(OBJS)

newton_main.o: newton_main.c newton.h


newton.o: newton.c newton.h


.PHONY: clean

clean:
	rm -f $(BINARY) *.o