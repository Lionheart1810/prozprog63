CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

all: blatt09_1_2.exe
blatt09_1_2.exe: blatt09_1_2.o
	$(CC) $(CFLAGS) -o blatt09_1_2.exe blatt09_1_2.o
blatt09_1_2.o: blatt09_1_2.c blatt09_1_2.h defs.h
	$(CC) $(CFLAGS) -c blatt09_1_2.c