#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//////////////////////////
#define DEBUG
#define _FOR_WINDOWS
#define HARDCODE
//////////////////////////

#define TRUE 1
#define FALSE 0

#define CHECK_ELEMENT(x, y) if (sudoku[y][x] != 0) { if ((checker >> (sudoku[y][x]-1)) & 1) return FALSE; else checker |= (1 << (sudoku[y][x]-1)); }
#define SUDOKU_READ(x, y) (sudoku[y][x] & 0xF)
#define SUDOKU_FLAG_PREDEFINED (1 << 7)
#define SUDOKU_FLAG_MODIFIED (1 << 6)
#define SUDOKU_IS_PREDEFINED(x) (x >> 7)
#define SUDOKU_IS_MODIFIED(x) ((x >> 6) & 1)

#ifdef DEBUG
#define DLOG(x) printf(x)
#else
#define DLOG(x) 
#endif

#ifdef _FOR_LINUX
#define CONSOLE_CLEAR system("clear")
#define COLOR_DEFAULT "\x1B[0m"
#define COLOR_PREDEFINED "\x1B[33m"
#define COLOR_MODIFIED "\x1B[32m"
#define COLOR_WRITABLE "\x1B[34m"
#endif
#ifdef _FOR_WINDOWS
#define CONSOLE_CLEAR system("cls")
#define COLOR_DEFAULT ""
#define COLOR_PREDEFINED ""
#define COLOR_MODIFIED ""
#define COLOR_WRITABLE ""
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long int u32;

struct placement
{
	u8 x;
	u8 y;
	u8 n;
	struct placement *next;
};

struct placement *undo_ptr, *redo_ptr;

void init();
u8 check(u8 x, u8 y, u8 n);
void set();
void undo();
void redo();
u8 solve(u8 overwrite);
u8 check_win();
u8 interpret(char *seq);
void reset();

#ifdef HARDCODE
u8 sudoku[9][9] = { { 4 | SUDOKU_FLAG_PREDEFINED, 1 | SUDOKU_FLAG_PREDEFINED, 0, 0, 6 | SUDOKU_FLAG_PREDEFINED, 5 | SUDOKU_FLAG_PREDEFINED, 0, 0, 7 | SUDOKU_FLAG_PREDEFINED },
					{ 0, 0, 6 | SUDOKU_FLAG_PREDEFINED, 0, 0, 7 | SUDOKU_FLAG_PREDEFINED, 4 | SUDOKU_FLAG_PREDEFINED, 8 | SUDOKU_FLAG_PREDEFINED, 0 },
					{ 2 | SUDOKU_FLAG_PREDEFINED, 0, 7 | SUDOKU_FLAG_PREDEFINED, 4 | SUDOKU_FLAG_PREDEFINED, 9 | SUDOKU_FLAG_PREDEFINED, 0, 0, 0, 6 | SUDOKU_FLAG_PREDEFINED },
					{ 0, 6 | SUDOKU_FLAG_PREDEFINED, 0, 0, 7 | SUDOKU_FLAG_PREDEFINED, 0, 1 | SUDOKU_FLAG_PREDEFINED, 0, 0 },
					{ 3 | SUDOKU_FLAG_PREDEFINED, 0, 1 | SUDOKU_FLAG_PREDEFINED, 5 | SUDOKU_FLAG_PREDEFINED, 0, 0, 0, 7 | SUDOKU_FLAG_PREDEFINED, 2 | SUDOKU_FLAG_PREDEFINED },
					{ 0, 9 | SUDOKU_FLAG_PREDEFINED, 0, 0, 4 | SUDOKU_FLAG_PREDEFINED, 2 | SUDOKU_FLAG_PREDEFINED, 3 | SUDOKU_FLAG_PREDEFINED, 0, 8 | SUDOKU_FLAG_PREDEFINED },
					{ 1 | SUDOKU_FLAG_PREDEFINED, 0, 8 | SUDOKU_FLAG_PREDEFINED, 6 | SUDOKU_FLAG_PREDEFINED, 0, 0, 0, 2 | SUDOKU_FLAG_PREDEFINED, 9 | SUDOKU_FLAG_PREDEFINED },
					{ 0, 2 | SUDOKU_FLAG_PREDEFINED, 0, 0, 1 | SUDOKU_FLAG_PREDEFINED, 8 | SUDOKU_FLAG_PREDEFINED, 6 | SUDOKU_FLAG_PREDEFINED, 4 | SUDOKU_FLAG_PREDEFINED, 0 },
					{ 6 | SUDOKU_FLAG_PREDEFINED, 0, 0, 3 | SUDOKU_FLAG_PREDEFINED, 0, 0, 0, 1 | SUDOKU_FLAG_PREDEFINED, 0 } };
#else
u8 sudoku[9][9] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
#endif

u8 check(u8 x, u8 y, u8 n)
{
        u8 n_old = sudoku[y][x];
        sudoku[y][x] = n;
        u16 checker = 0;
        // check row
        for (u8 i = 0; i < 9; i++)
        {
            if (SUDOKU_READ(i, y) != 0)
            {
                if ((checker >> (SUDOKU_READ(i, y)-1)) & 1)
                {
                    goto failed;
                }
                else
                    checker |= (1 << (SUDOKU_READ(i, y)-1));
            }
        }
        // check column
        checker = 0;
        for (u8 i = 0; i < 9; i++)
        {
            if (SUDOKU_READ(x, i) != 0)
            {
                if ((checker >> (SUDOKU_READ(x, i)-1)) & 1)
                {
                    goto failed;
                }
                else
                    checker |= (1 << (SUDOKU_READ(x, i)-1));
            }
        }
        // check block
        checker = 0;
        for (u8 by = y-(y%3), zy = y-(y%3)+3; by < zy; by++)
        {
            for (u8 bx = x-(x%3), zx = x-(x%3)+3; bx < zx; bx++)
            {
                if (SUDOKU_READ(bx, by) != 0)
                {
                    if ((checker >> (SUDOKU_READ(bx, by)-1)) & 1)
                    {
                        goto failed;
                    }
                    else
                        checker |= (1 << (SUDOKU_READ(bx, by)-1));
                }
            }
        }
        sudoku[y][x] = n_old;
        return TRUE;
        failed: sudoku[y][x] = n_old;
        DLOG("durchgefallen\n");
        return FALSE;
}

void set()
{
	u32 x, y, n;
	printf("X: ");
	scanf("%lu", &x);
	printf("Y: ");
	scanf("%lu", &y);
	printf("Number: ");
	scanf("%lu", &n);
	x--; y--;
	if ((!(sudoku[y][x] >> 7)) && check(x, y, n))
	{
		struct placement *e = malloc(sizeof(struct placement));
		e->x = x;
		e->y = y;
		e->n = sudoku[y][x];
		e->next = undo_ptr;
		undo_ptr = e;
		sudoku[y][x] = n | SUDOKU_FLAG_MODIFIED;
		// clear redo stack
		struct placement *buf;
		while (redo_ptr)
		{
			buf = redo_ptr->next;
			free(redo_ptr);
			redo_ptr = buf;
		}
	}
	else
		printf("Illegal placement!\n");
}

void undo()
{
	u32 t;
	printf("Undo how many steps: ");
	scanf("%lu", &t);
	for (u32 i = 0; i < t; i++)
	{
		if (undo_ptr)
		{
			struct placement *e = malloc(sizeof(struct placement));
			struct placement *buf = undo_ptr;
			e->x = undo_ptr->x;
			e->y = undo_ptr->y;
			e->n = sudoku[e->y][e->x];
			e->next = redo_ptr;
			sudoku[undo_ptr->y][undo_ptr->x] = undo_ptr->n;
			redo_ptr = e;
			undo_ptr = undo_ptr->next;
			free(buf);
		}
		else
		{
			printf("Reached end of undo stack.\n");
			break;
		}
	}
}

void redo()
{
	u32 t;
	printf("Redo how many steps: ");
	scanf("%lu", &t);
	for (u32 i = 0; i < t; i++)
	{
		if (redo_ptr)
		{
			struct placement *e = malloc(sizeof(struct placement));
			struct placement *buf = redo_ptr;
			e->x = redo_ptr->x;
			e->y = redo_ptr->y;
			e->n = sudoku[e->y][e->x];
			e->next = undo_ptr;
			sudoku[redo_ptr->y][redo_ptr->x] = redo_ptr->n;
			undo_ptr = e;
			redo_ptr = redo_ptr->next;
			free(buf);
		}
		else
		{
			printf("Reached end of redo stack.\n");
			break;
		}
	}
}

u8 interpret(char *seq)
{
	switch(seq[0])
	{
	case 'h':
		printf("-- Actions --\ns[e[t[*[*]]]]: Set a number at a given position\nu[n[d[o[*]]]]: Undo last action\nred[o[*]]: Redo last action\nres[e[t]]: Reset current sudoku\ne[x[i[t[*]]]]: Exit the program\n");
		getchar();
		getchar();
		break;
	case 's':
		set();
		break;
	case 'u':
		undo();
		break;
	case 'r':
		redo();
		break;
	case 'e':
		return FALSE;
	default:
		printf("Couldnt interpret sequence, type h[e[l[p]]] for more info.\n");
		getchar();
		getchar();
		break;
	}
	return TRUE;
}

void init(u32 filled)
{
    DLOG("init\n");
	u8 r = 0;
	srand(time(NULL));
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			if (((u32)rand() % 100) < filled)
			{
				while (!check(x, y, r = ((u8)rand() % 9) + 1));
				sudoku[y][x] = r | SUDOKU_FLAG_PREDEFINED;
			}
		}
	}
}

u8 check_win()
{
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			if (SUDOKU_READ(x, y) == 0)
				return FALSE;
		}
	}
	return TRUE;
}

void reset()
{
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			if (!SUDOKU_IS_PREDEFINED(sudoku[y][x]))
			{
				sudoku[y][x] = 0;
			}
		}
	}
}

u8 solve(u8 overwrite)
{
	// TODO
	return FALSE;
	/*
	struct key keys[9][9];
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			keys[y][x] = struct key{0, 0, 0};
		}
	}
	if (overwrite)
		reset();
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			if (!SUDOKU_IS_PREDEFINED(sudoku[y][x]))
			{
				for (u8 i = 1; i < 10; i++)
				{
					if (check(x, y, i))
						keys[y][x].possible_solutions |= (1 << i);
				}
				if (keys[y][x].possible_solutions[y][x] == 0)
					return FALSE;
			}
		}
	}
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			for (; ; keys[y][x].current++)
			{
				// TODO
				//keys[y][x].possible_solutions >>=
			}
		}
	}
	*/
}

int main(int argc, char **argv)
{
	char action[5];
	#ifndef HARDCODE
	init((argc == 2) ? atoi(argv[1]) : 50);
	#endif
	while (TRUE)
	{
		#ifndef DEBUG
        CONSOLE_CLEAR;
		#endif
		// Ausgabe des Spielfeldes
		printf("  | 1 2 3 | 4 5 6 | 7 8 9 |\n--+-------+-------+-------+\n");
		for (u8 y = 0; y < 9; y++)
		{
			printf("%d ", y+1);
			for (u8 x = 0; x < 9; x++)
			{
				printf((x % 3 == 0) ? "| %s%d%s " : "%s%d%s ", (SUDOKU_IS_MODIFIED(sudoku[y][x]) ? COLOR_MODIFIED : (SUDOKU_IS_PREDEFINED(sudoku[y][x]) ? COLOR_PREDEFINED : COLOR_WRITABLE)), SUDOKU_READ(x, y), COLOR_DEFAULT);
			}
			printf(((y+1) % 3 == 0) ? "|\n--+-------+-------+-------+\n" : "|\n");
		}
		// Abfrage von Aktion
		printf("Action: ");
		scanf("%5s", action);
		if (!interpret(action)) break;
		if (check_win())
		{
			printf("SUDOKU SOLVED! CONGRATULATIONS!");
			break;
		}
	}
	return 0;
}