LIBS  = -lX11
CFLAGS = -I. -L/usr/X11R6/lib 


# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.c)

all: $(SRC)
	gcc -o test $^ $(CFLAGS) $(LIBS)