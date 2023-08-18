CC = gcc
CFLAGS := -Wall -Wno-parentheses

all:
	$(CC) crc13tab.c $(CFLAGS) -o crc13tab
	chmod u+x ./crc13tab; ./crc13tab
	rm -f ./crc13tab
	$(CC) crc13.c $(CFLAGS) -o crc13

clean:
	rm -f ./crc13tab ./crc13 ./crc13_tab.h 
