#include <stdio.h>
#include <stdint.h>

int main(){
	for(int N = 1; N < 10; N++){
		for(int i = -(N-1); i < N; i++){
			for(int j = 0; j < abs(i); j++){
				printf("  ");
			}
			if(N - abs(i) < 2){
			  printf("1");
			}
			else{
				int z = abs(N-1-abs(i));
				for(int h = -z; h < z+1; h++){
				  printf("%d ", (N - abs(i)) - abs(h));
				}
			}
		  printf("\n");
		}
	}
}
