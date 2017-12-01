#include <stdio.h>
#include <stdlib.h>
#include "libBMP.h"

/////////////////////////////////////////
#define FUNKTION_TUTOR(x) x*x*x
#define OUTPUT_PATH "C:\\Users\\Superleo1810\\Desktop\\test.bmp"
#define COLOR_AXES 0xAAAAAA
#define COLOR_GRAPH 0
#define DIMENSIONS_X 1000
#define DIMENSIONS_Y 1000
#define WINDOW_MIN_X -10.0f
#define WINDOW_MIN_Y -10.0f
#define WINDOW_MAX_X 10.0f
#define WINDOW_MAX_Y 10.0f
#define INTERPOLATION
#define DEBUG 
/////////////////////////////////////////

typedef signed long int s32;
typedef unsigned long int u32;
typedef unsigned long long u64;

typedef struct
{
	u32 x;
	u32 y;
} Vector2i;

typedef struct
{
	float x;
	float y;
} Vector2f;

u32 *image;
Vector2i dimensions;
Vector2f window_min, window_max;
char *output;

// Helper functions, general context
void toMath(Vector2i dimensions, Vector2f window_min, Vector2f window_max, Vector2i coords_bmp, Vector2f *coords_math);
void toDiscrete(Vector2i dimensions, Vector2f window_min, Vector2f window_max, Vector2f coords_math, Vector2i *coords_bmp);
// Functions of specific context
void draw_point_math(Vector2f coords_math, u32 color);

void toMath(Vector2i dimensions, Vector2f window_min, Vector2f window_max, Vector2i coords_bmp, Vector2f *coords_math)
{
	coords_math->x = window_min.x + (coords_bmp.x * (window_max.x - window_min.x))/dimensions.x;
	coords_math->y = window_min.y + (coords_bmp.y * (window_max.y - window_min.y))/dimensions.y;
}

void toDiscrete(Vector2i dimensions, Vector2f window_min, Vector2f window_max, Vector2f coords_math, Vector2i *coords_bmp)
{
	Vector2f _coords_bmp;
	_coords_bmp.x = ((coords_math.x - window_min.x) * dimensions.x) / (window_max.x - window_min.x);
	_coords_bmp.y = dimensions.y - ((coords_math.y - window_min.y) * dimensions.y) / (window_max.y - window_min.y);
	coords_bmp->x = ((_coords_bmp.x + 0.5f) > ((u32)_coords_bmp.x + 1)) ? ((u32)_coords_bmp.x + 1) : (u32)_coords_bmp.x;
	coords_bmp->y = ((_coords_bmp.y + 0.5f) > ((u32)_coords_bmp.y + 1)) ? ((u32)_coords_bmp.y + 1) : (u32)_coords_bmp.y;
}

void draw_point_math(Vector2f coords_math, u32 color)
{
	Vector2i _coords_bmp;
	toDiscrete(dimensions, window_min, window_max, coords_math, &_coords_bmp);
	if (_coords_bmp.x < dimensions.x && _coords_bmp.y < dimensions.y)
		image[(_coords_bmp.y * dimensions.x) + _coords_bmp.x] = color;
}

int main(int argc, char **argv)
{
	output = (argc > 1) ? argv[1] : OUTPUT_PATH;
	dimensions.x = (argc > 2) ? atoi(argv[2]) : DIMENSIONS_X;
	dimensions.y = (argc > 3) ? atoi(argv[3]) : DIMENSIONS_Y;
	window_min.x = (argc > 4) ? atof(argv[4]) : WINDOW_MIN_X;
	window_min.y = (argc > 5) ? atof(argv[5]) : WINDOW_MIN_Y;
	window_max.x = (argc > 6) ? atof(argv[6]) : WINDOW_MAX_X;
	window_max.y = (argc > 7) ? atof(argv[7]) : WINDOW_MAX_Y;
	image = malloc(dimensions.x * dimensions.y * sizeof(u32));
	// Init
	for (size_t i = 0, sz = dimensions.x * dimensions.y; i < sz; i++)
		image[i] = (u32)~0;
	// Draw axes
	Vector2f coords_math;
	Vector2i coords_bmp, coords_bmp_old;
	coords_bmp_old.x = 0;
	coords_bmp_old.y = 0;
	for (Vector2i x = { 0, 0 }; x.x < dimensions.x; x.x++)
	{
		toMath(dimensions, window_min, window_max, x, &coords_math);
		coords_math.y = 0.0f;
		draw_point_math(coords_math, COLOR_AXES);
	}
	for (Vector2i y = { 0, 0 }; y.y < dimensions.y; y.y++)
	{
		toMath(dimensions, window_min, window_max, y, &coords_math);
		coords_math.x = 0.0f;
		draw_point_math(coords_math, COLOR_AXES);
	}
	// Draw graph
	for (Vector2i x = { 0, 0 }; x.x < dimensions.x; x.x++)
	{
		toMath(dimensions, window_min, window_max, x, &coords_math);
		coords_math.y = FUNKTION_TUTOR(coords_math.x);
		toDiscrete(dimensions, window_min, window_max, coords_math, &coords_bmp);
		if (coords_bmp.x < dimensions.x && coords_bmp.y < dimensions.y)
		{
			image[(coords_bmp.y * dimensions.x) + coords_bmp.x] = COLOR_GRAPH;
			// Interpolation
			#ifdef INTERPOLATION
			s32 diff = coords_bmp.y - coords_bmp_old.y;
			if (diff < 0)
			{
				for (s32 i = 0, k = diff / 2; i > k; i--)
				{
					image[((coords_bmp_old.y + i) * dimensions.x) + coords_bmp_old.x] = COLOR_GRAPH;
				}
				for (s32 i = diff / 2; i > diff; i--)
				{
					image[((coords_bmp_old.y + i) * dimensions.x) + coords_bmp.x] = COLOR_GRAPH;
				}
			}
			else
			{
				for (s32 i = 0, k = diff / 2; i < k; i++)
				{
					image[((coords_bmp_old.y + i) * dimensions.x) + coords_bmp_old.x] = COLOR_GRAPH;
				}
				for (s32 i = diff / 2; i < diff; i++)
				{
					image[((coords_bmp_old.y + i) * dimensions.x) + coords_bmp.x] = COLOR_GRAPH;
				}
			}
			memcpy(&coords_bmp_old, &coords_bmp, sizeof(Vector2i));
			#endif
		}
		
	}
	bmp_create(output, image, dimensions.x, dimensions.y);
	free(image);
	return 0;
}
