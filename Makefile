CC=gcc
CFLAGS=-pedantic -ansi -Wall -Werror
CFILES=index.c main.c


all:
	$(CC) $(CFILES) $(CFLAGS) -o index

debug:
	$(CC) -g $(CFILES)  $(CFLAGS) -o index

clean:
	rm index
