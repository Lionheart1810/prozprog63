#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
		char Vorname[20];
		char Nachname[20];
		int Matrikelnummer;
		char Adresse[30];
		short Pflichtkurse;
		struct student *next;
		struct student *prev;
	};

struct student *start;
struct student *startfix;
struct student *lastentry;
struct student *delete;
struct student *end;

void swap(struct student **a, struct student **b){
    struct student** temp = *a;
    *a = *b;
    *b = temp;
}

void buildlinkedlist(){
	int n , m;
	printf("Anzahl : ");
	scanf("%d", &n);
	m = n;

	if(startfix == NULL){
		startfix = start = lastentry = (struct student*) malloc(sizeof(struct student));
		strcpy(start->Vorname,"Max");
		strcpy(start->Nachname,"Mustermann");
		start->Matrikelnummer = 42;
		strcpy(start->Adresse,"Musterstrasse");
		start->Pflichtkurse = 0;
		start->next = NULL;
		start->prev = NULL;
		end = start;
		m--;
	}
	for(int i = 0; i < m; i++){
		end->next = (struct student*) malloc(sizeof(struct student));
		strcpy(end->next->Vorname, "na");
		end->next->prev = end;
		end = end->next;
	}
	end->next = NULL;

	printf("%d student structs created", n);
}

void getstudents(){
	int n;
	char buffer[20];
	int bufferint;
	printf("Anzahl : ");
	scanf("%d", &n);
	start = lastentry;
	//printf("Vorname Nachname Matrikelnummer Adresse Pflichtkurse \n");
	while(lastentry->next != NULL && n--){
		printf("Noch %d Studenten \n", n+1);

		printf(" Vorname: ");
		scanf("%s", buffer);
		strcpy(start->next->Vorname, buffer);

		printf("\n Nachname: ");
		scanf("%s", buffer);
		strcpy(start->next->Nachname, buffer);

		printf("\n Matrikelnummer: ");
		scanf("%d", &bufferint);
		start->next->Matrikelnummer = bufferint;

		printf("\n Adresse: ");
		scanf("%s", buffer);
		strcpy(start->next->Adresse, buffer);

		printf("\n Pflichtkurse: ");
		scanf("%d", &bufferint);
		start->next->Pflichtkurse = bufferint;

		lastentry = start->next;
		start = start->next;
	}
}

// void getstudents(){
	// FILE *fstudents = fopen( "students.txt", "r" );
	// char *line = NULL;
	// size_t len = 0;
	// ssize_t read;

	// while ((read = getline(&line, &len, fstudents)) != -1) {
		// if(start == NULL){
			// printf("Not enough memory available");
			// return(0);
		// }
		// sscanf(read, "%s %s %d %s %d", &(start->Vorname), &(start->Nachname), &(start->Matrikelnummer), &(start->Adresse), &(start->Pflitchtkurse));
		// start = start->next;
	// }
// }

void autofill(){
	if(lastentry->next == NULL){
		printf("Not enough memory");
	}
	else{
		if(lastentry->next != NULL && startfix != NULL){
			printf("copying...");
			strcpy(lastentry->next->Vorname,"Anna");
			strcpy(lastentry->next->Nachname,"Musterfrau");
			lastentry->next->Matrikelnummer = 4444;
			strcpy(lastentry->next->Adresse,"Kasernenstrasse 12");
			lastentry->next->Pflichtkurse = 5;
			lastentry = lastentry->next;
		}
		if(lastentry->next != NULL && startfix != NULL){
			printf("copying...");
			strcpy(lastentry->next->Vorname,"Linus");
			strcpy(lastentry->next->Nachname,"Torvalds");
			lastentry->next->Matrikelnummer = 145;
			strcpy(lastentry->next->Adresse,"Kasernenstrasse 1222");
			lastentry->next->Pflichtkurse = 42;
			lastentry = lastentry->next;
		}
		if(lastentry->next != NULL && startfix != NULL){
			printf("copying...");
			strcpy(lastentry->next->Vorname,"Peter");
			strcpy(lastentry->next->Nachname,"DeleteMe");
			lastentry->next->Matrikelnummer = 9535;
			strcpy(lastentry->next->Adresse,"Kasernenstrasse 122");
			lastentry->next->Pflichtkurse = 7;
			lastentry = lastentry->next;
		}
		if(lastentry->next != NULL && startfix != NULL){
			printf("copying...");
			strcpy(lastentry->next->Vorname,"Torben");
			strcpy(lastentry->next->Nachname,"Maler");
			lastentry->next->Matrikelnummer = 12345;
			strcpy(lastentry->next->Adresse,"Kasernenstrasse 1222");
			lastentry->next->Pflichtkurse = 97;
			lastentry = lastentry->next;
		}
		if(lastentry->next != NULL && startfix != NULL){
			printf("copying...");
			strcpy(lastentry->next->Vorname,"Konrad");
			strcpy(lastentry->next->Nachname,"Zuse");
			lastentry->next->Matrikelnummer = 1234225;
			strcpy(lastentry->next->Adresse,"Kasernenstrasse 12222");
			lastentry->next->Pflichtkurse = 43;
			lastentry = lastentry->next;
		}
	}
}

void print_student(){
	start = startfix;
	if(start == NULL){
		printf("No student entry");
	}
	else{
		do{
			if(strcmp(start->Vorname,"na")){
				printf("%s   %s   %d   %s   %d \n", start->Vorname, start->Nachname, start->Matrikelnummer, start->Adresse, start->Pflichtkurse);
			}
			start = start->next;
		}while(start != NULL);
		printf("\n");
	}
}

void deleteentry(){
	int i;
	printf("Nummer:");
	scanf("%d", &i);
	delete = startfix;

	for(int j = 1  ; j < i; j++){
		delete = delete->next;
	}

	delete->prev->next = delete->next;
	delete->next->prev = delete->prev;
	free(delete);
}

void sort(){

	int cp;
    int n = 0;
	start = startfix;
	if(start != NULL) n++;
	while(start->next != NULL){
		n++;
		start = start->next;
	}
    print_student();
	for(int i = 0; i < n; i++){
		struct student *pstart = startfix;
		for(int j = 0; j < n-1; j++){
            if(pstart->next != NULL){
                cp = strcmp(pstart->Nachname, pstart->next->Nachname);
                //getchar();
                if(cp > 0){
                    if(pstart->prev == NULL){
                        struct student *pbuffer = pstart->next;
                        struct student *pbuffer2 = pstart->next->next;
                        struct student *pbuffer3 = pstart->prev;
                        startfix = pbuffer;
                        pstart->next = pbuffer2;
                        pbuffer->next = pstart;

                        pbuffer->prev = NULL;
                        pstart->prev = pbuffer;
                        pbuffer2->prev = pstart;

                    }

                    else if(pstart->next->next == NULL){
                        struct student *pbuffer = pstart->next;
                        struct student *pbuffer2 = pstart->next->next;
                        //struct student *pbuffer3 = pstart->next->next->prev;
                        struct student *pbuffer4 = pstart->prev;
                        struct student *pbuffer5 = pstart->prev->next;
                        pstart->next = NULL;
                        pbuffer->next = pstart;
                        pstart->prev->next == pbuffer;

                        pstart->prev = pbuffer;
                        //pbuffer2->prev = pstart;
                        pbuffer->prev = pbuffer4;
                    }
                    else{
                        struct student *pbuffer = pstart->next;
                        struct student *pbuffer2 = pstart->next->next;
                        struct student *pbuffer3 = pstart->next->next->prev;
                        struct student *pbuffer4 = pstart->prev;
                        struct student *pbuffer5 = pstart->prev->next;
                        pstart->prev->next = pbuffer;
                        pbuffer->next = pstart;
                        pstart->next = pbuffer2;

                        pbuffer->prev = pbuffer4;
                        pstart->prev = pbuffer;
                        pbuffer2->prev = pstart;
                    }
                    struct student *pbuffer3 = pstart;
                    print_student();
                    //getchar();
                    pstart = pbuffer3;
                }
                else{
                    pstart = pstart->next;
                }
            }
		}
	}
	printf("Sortiert");
}

void changeorder(){
	struct student *pbuffer;
	end = startfix;
	while(end->next != NULL){
		end = end->next;
	}
	pbuffer = startfix;
	start = startfix;

	while(pbuffer != NULL){
		start = pbuffer;
		pbuffer = pbuffer->next;
		swap(&start->next, &start->prev);
	}
    swap(&startfix, &end);
	lastentry = end;
	end->next = NULL;
}

void list_length(){
	int i = 0;
	int j = 0;
	start = startfix;
	if(start != NULL) i++, j++;
	while(start->next != NULL){
		if(strcmp(start->Vorname, "na")){
			j++;
		}
		i++;
		start = start->next;
	}
	printf("Die doppelt verkettete Liste besteht aus %d Structs\nund hat %d Eintraege.", i, j);
}

void (*funcs[8])(void) = { buildlinkedlist, getstudents, autofill, print_student, list_length, deleteentry, changeorder, sort };

void freeall(){
	delete = start = startfix;
	while(start->next != NULL){
		start = delete->next;
		free(delete);
		delete = start;
	}
}

int main(){
	int in = 0;
	getchar();
	system("cls");
	do
	{
		printf("1) Studenten anlegen	       2) Einlesen \n");
		printf("3) Autofill                    4) Ausgeben \n");
		printf("5) Listen Laenge               6) Eintrag loeschen\n");
		printf("7) Reihenfolge aendern         8) Alphabetisch sortieren\n");
		do in = getchar()-48; while (in < 1 || in > 8);
		funcs[in-1]();
		getch();
		system("cls");
	}
	while (in != 9);

	freeall();
	return(0);
}



