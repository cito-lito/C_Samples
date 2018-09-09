

OBJS = ggt.o ggtmain.o
CFLAGS = -Wall
BINARY = ggt

all: $(BINARY)
	
$(BINARY): $(OBJS)
	gcc -g $(CFLAGS) -o $@ $(OBJS)

ggt.o: ggt.c ggt.h

ggtmain.o: ggtmain.c ggt.h


.PHONY: clean

clean: 
	rm -f $(BINARY) *.o
