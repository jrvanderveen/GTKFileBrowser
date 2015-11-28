EXES = fb
FBOBJ = FB.o TreeView/buildTree.o
CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags --libs gtk+-3.0`

all:    $(EXES)

fb:     $(FBOBJ)
	$(CC) -o $@ $(FBOBJ) $(CFLAGS)
%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -f $(EXES) *.o

