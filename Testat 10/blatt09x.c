#include <stdio.h>

struct student{
		char *Vorname;
		char *Nachname;
		int Matrikelnummer;
		char *Adresse;
		short Pflitchtkurse;
	};
	
struct student s1 = { " Anna " , " Musterfrau " , 22222 , " Am Schwarzenberg - Campus 3 " , 4 };
struct student s2 = { " Hans " , " Peter " , 44444 , " Kasernenstrasse 12 " , 2 };
struct student s3 = { " Lisa " , " Lustig " , 66666 , " Denickestrasse 15 " , 8 };


void print(int padress[]){
	for(int i = 0; i < 3; i++){		
		struct student *sptr;
		sptr = padress[i];
		printf("%s   %s   %d   %s   %d \n", sptr->Vorname, sptr->Nachname, sptr->Matrikelnummer, sptr->Adresse, sptr->Pflitchtkurse);
	}
}

int main(){
	system("cls");
	int padress[3] = {(long)&s1, (long)&s2, (long)&s3};
	
	print(padress);
	
	printf("\n\n\n");
	
	int a = padress[0];
	padress[0] = padress[2];
	padress[2] = a;
	
	print(padress);
}