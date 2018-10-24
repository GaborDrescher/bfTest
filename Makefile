.PHONY: all clean

CC = gcc
WARN = -Wall -Wextra
CFLAGS = $(WARN) -std=c99 -O3

all: goto switch

goto: bf.o emugoto.o
	$(CC) $(CFLAGS) -o $@ $^

switch: bf.o emuswitch.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f goto switch *.o
