CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

all: blatt08_1.exe
blatt08_1.exe: blatt08_1.o sort.o
	$(CC) $(CFLAGS) -o blatt08_1.exe blatt08_1.o sort.o
sort.o: sort.c sort.h defs.h
	$(CC) $(CFLAGS) -c sort.c
blatt08_1.o: blatt08_1.c blatt08_1.h sort.h defs.h
	$(CC) $(CFLAGS) -c blatt08_1.c