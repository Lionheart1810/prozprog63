#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint16_t u16;
typedef unsigned char u8; 

int main(int argc, char **argv) {
	printf("\n\nblatt02_2_1 - Aufgabe 2.1\n\n");
	for (u16 i = 0; i <= 550; i+=5)
		printf("%dK = %dC\n", i, i-273);
	return 0;
}

//  int main(){
  // for(int k = 0; k < 551; k = k + 5){
    // int c = k - 273;
    // if(k < 10){
      // printf("  ");
    // }else if(k < 100){
      // printf(" ");
    // }
    // printf("kelvin: %d || celsius: %d \n", k,c);
    // }
  
// }
// 