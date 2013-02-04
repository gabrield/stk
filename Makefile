CC=gcc
CFLAGS=-c -g -I. -Wall 
LDFLAGS=-L/usr/X11R6/lib -lX11
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) test
