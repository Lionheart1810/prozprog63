#include "blatt09_1_2.h"

Student studenten[3];

int main()
{
	studenten[0] = (Student) { "Anna" , "Musterfrau" , 22222 , "Am Schwarzenberg-Campus 3" , 4};
	studenten[1] = (Student) { "Hans", "Peter", 44444, "Kasernenstrasse 12", 2};
	studenten[2] = (Student) { "Lisa", "Lustig", 66666, "Denickestrasse 15", 8};
	print_studenten();
	printf("tausche 1 mit 3\n");
	swap(studenten, studenten + 2);
	print_studenten();
}

void print_studenten()
{
	for (u8 i = 0, sz = sizeof(studenten)/sizeof(Student); i < sz; i++)
		printf("{\"%s\", \"%s\", %u, \"%s\", %u}\n", studenten[i].vorname, studenten[i].nachname, studenten[i].matrikelnummer, studenten[i].adresse, studenten[i].kurse);
}

void swap(Student *s1, Student *s2)
{
	struct student buffer = *s1;
	*s1 = *s2;
	*s2 = buffer;
}