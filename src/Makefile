CC=gcc
CFLAGS=-c -g -I. -pedantic -Wall 
LDFLAGS=-L/usr/X11R6/lib -lX11
SOURCES=$(wildcard *.c)

OBJECTS=$(SOURCES:.c=.o)


all: $(OBJECTS) 
	gcc *.o -o test -lX11

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJECTS) test
