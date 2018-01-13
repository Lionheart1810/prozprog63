#include <stdio.h>
#include <stdint.h>

int main(){
	for(int N = 1; N < 10; N++){							//Schleife für alle Rauten
		for(int i = -(N-1); i < N; i++){					/// i = Zeilennummer
															//Die Raute mit N ist aus 2N-1 Zeilen aufgebaut. Die Zeilennummer laufen von -(N-1) bis N, sodass in der Zeile 0 N vorkommt.
			for(int j = 0; j < abs(i); j++){				/// j = Leerzeichen
															//Durch den symetrischen Aufbau der Raute können in der n-ten Zeile n Leerzeichen ausgegeben werden.
				printf("  ");
			}
			if(N - abs(i) < 2){								//In der ersten und letzen Zeile muss nur die 1 ausgegeben werden.
			  printf("1");
			}
			else{
				int z = abs(N-1-abs(i));								
				for(int h = -z; h < z+1; h++){				/// h = Durchlauf der Zahlen
				  printf("%d ", (N - abs(i)) - abs(h));		//In der n-ten Zeile ist die höchste Zahl N - |n|. Die Schleife läuft von der 1 bis zur höchsten Zahl und dann wieder zurück zur 1. 
				}
			}
		  printf("\n");
		}
	}
}
