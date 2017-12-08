#include <stdio.h>
#include "libBMP.h"
#include <math.h>

#define W 3000
#define H 2000

#define X_MIN -2.0
#define X_MAX 1.0

#define Y_MIN -1.001
#define Y_MAX 1.001

#define N_MAX 100



int n = 0;
double x = 0.0, y = 0.0;


int Mandelbrot(double x, double y, double cx, double cy, int n){
	if(((x*x)+(y*y) <= 4) && (n < N_MAX)){
		double x2 = x;
		x = (x*x) - (y*y) + cx;
		y = 2.0*x2*y + cy;
		n = Mandelbrot(x, y, cx, cy, n+1);
	}
	return(n);
}

void toBMP(float x, float y, uint32_t *X, uint32_t *Y){
	*X = (int)round((x - X_MIN)*W/(X_MAX-X_MIN));
	*Y = (int)round(H - (y - Y_MIN)*H/(Y_MAX-Y_MIN));
}

int main(){

	uint32_t* data = (uint32_t*) malloc(W * H * sizeof(uint32_t));
	for(int i = 0; i < H; i++){
		for(int j = 0; j < W; j+=2){
			data[i*W+j] = COLOR_WHITE;
		}
	}
	for(int i = 0; i < H; i++){
		for(int j = 1; j < W; j+=2){
			data[i*W+j] = COLOR_WHITE;
		}
	}
	
	uint32_t X = 0, Y = 0;

	for(double cx = -2.0; cx < 1.0001; cx +=0.0001){
		for(double cy = -1.0; cy < 1.0001; cy += 0.0001){
			n = Mandelbrot(x, y, cx, cy, 0);
			

			toBMP(cx, cy, &X, &Y);
			
			if(n < 30){
				data[Y*W+X] = COLOR_WHITE;
			}
			else if(n < 60){
				data[Y*W+X] = COLOR_BLUE;
			}
			else if(n < 80){
				data[Y*W+X] = COLOR_RED;
			}
			else
				if(n < 101){
				data[Y*W+X] = COLOR_BLACK;
			}							
		}
	}

	bmp_create("Mandelbrot.bmp",data, W, H);
	free(data);
}
