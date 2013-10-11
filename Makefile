CC=gcc
CFLAGS=-pedantic -ansi -Wall -Werror -o
CFILES=tokenizer.c index.c main.c -o index


all:
	$(CC) $(CFILES) $(CFLAGS) index

debug:
	$(CC) -g $(CFILES)  $(CFLAGS) index

clean:
	rm index
