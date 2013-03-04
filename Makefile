CC=gcc
CFLAGS=-c -g -I. -Wall 
LDFLAGS=-L/usr/X11R6/lib -lX11
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test
STK_OBJS=$(wildcard stk*.o)



docs:
	@cd doc && make

all: $(SOURCES) $(EXECUTABLE)

	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) test *.a doc/*.html

lib:
	ar rcs libstk.a $(STK_OBJS)
