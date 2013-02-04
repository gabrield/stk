LIBS  = -lX11
CFLAGS = -g -I. -L/usr/X11R6/lib -Wall 

SRC=$(wildcard *.c)

all: $(SRC)
	gcc -o test $^ $(CFLAGS) $(LIBS)