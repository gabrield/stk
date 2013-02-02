LIBS  = -lX11
CFLAGS = -I. -L/usr/X11R6/lib -Wall -g

SRC=$(wildcard *.c)

all: $(SRC)
	gcc -o test $^ $(CFLAGS) $(LIBS)