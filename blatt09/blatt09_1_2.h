#ifndef BLATT09_1_2
#define BLATT09_1_2

#include "defs.h"

typedef struct student{
	char *vorname;
	char *nachname;
	u32 matrikelnummer;
	char *adresse;
	u8 kurse;
} Student;

int main();
void print_studenten();
void swap(Student *s1, Student *s2);

#endif