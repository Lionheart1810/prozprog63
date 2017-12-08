#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//////////////////////////
//#define DEBUG
#define _FOR_WINDOWS
//#define HARDCODE
//////////////////////////

#define TRUE 1
#define FALSE 0

#define CHECK_ELEMENT(x, y) if (sudoku[y][x] != 0) { if ((checker >> (sudoku[y][x]-1)) & 1) return FALSE; else checker |= (1 << (sudoku[y][x]-1)); }
#define SUDOKU_READ(x, y) (sudoku[y][x] & 0xF)
#define SUDOKU_FLAG_PREDEFINED (1 << 7)
#define SUDOKU_FLAG_MODIFIED (1 << 6)
#define SUDOKU_FLAG_SOLVING (1 << 5)
#define SUDOKU_IS_PREDEFINED(x) (x >> 7)
#define SUDOKU_IS_MODIFIED(x) ((x >> 6) & 1)
#define SUDOKU_IS_SOLVING(x) ((x >> 5) & 1)

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
void solve();
u8 _set(u32 x, u32 y, u32 n);
u8 _undo(u32 n);
u8 _redo(u32 n);
#ifdef DEBUG
u8 _solve(u32 level);
#else
u8 _solve();
#endif
void _clear();
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
        //DLOG("durchgefallen\n");
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
	if (!_set(x, y, n))
	{
		printf("Illegal placement!\n");
	}
}

void undo()
{
	u32 t;
	printf("Undo how many steps: ");
	scanf("%lu", &t);
	if(!_undo(t))
		printf("Reached end of undo stack.\n");
}

void redo()
{
	u32 t;
	printf("Redo how many steps: ");
	scanf("%lu", &t);
	if(!_redo(t))
		printf("Reached end of redo stack.\n");
}

void solve()
{
	#ifdef DEBUG
	if (!_solve(0))
	#else
	if (!_solve())
	#endif
		printf("Sudoku not solvable!\n");
}

u8 _set(u32 x, u32 y, u32 n)
{
	if ((!SUDOKU_IS_PREDEFINED(sudoku[y][x])) && check(x, y, n))
	{
		struct placement *e = malloc(sizeof(struct placement));
		e->x = x;
		e->y = y;
		e->n = sudoku[y][x];
		e->next = undo_ptr;
		undo_ptr = e;
		sudoku[y][x] = n | (sudoku[y][x] & 0xF0) | SUDOKU_FLAG_MODIFIED;
		// clear redo stack
		struct placement *buf;
		while (redo_ptr)
		{
			buf = redo_ptr->next;
			free(redo_ptr);
			redo_ptr = buf;
		}
		return TRUE;
	}
	return FALSE;
}

u8 _undo(u32 n)
{
	if (n == 0)
		n = ~0;
	for (u32 i = 0; i < n; i++)
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
			return FALSE;
	}
	return TRUE;
}

u8 _redo(u32 n)
{
	if (n == 0)
		n = ~0;
	for (u32 i = 0; i < n; i++)
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
			return FALSE;
	}
	return TRUE;
}

#ifdef DEBUG
u8 _solve(u32 level)
{
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			if (!SUDOKU_IS_PREDEFINED(sudoku[y][x]) && !SUDOKU_IS_SOLVING(sudoku[y][x]))
			{
				sudoku[y][x] |= SUDOKU_FLAG_SOLVING;
				//printf("%d%d%d%d%d%d%d%d\n", (sudoku[y][x] >> 7) & 1, (sudoku[y][x] >> 6) & 1, (sudoku[y][x] >> 5) & 1, (sudoku[y][x] >> 4) & 1, (sudoku[y][x] >> 3) & 1, (sudoku[y][x] >> 2) & 1, (sudoku[y][x] >> 1) & 1, sudoku[y][x] & 1);
				for (u8 n = 1; n < 10; n++)
				{
					printf("[Level %d] setting: { %d, %d, %d }\n", level, x, y, n);
					if (_set(x, y, n))
					{
						printf("[Level %d] set: %d\n", level, n);
						if(_solve(level + 1))
						{
							return TRUE;
						}
					}
				}
				sudoku[y][x] = 0;
				return FALSE;
			}
		}
	}
	return TRUE;
}
#else
u8 _solve()
{
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			if (!SUDOKU_IS_PREDEFINED(sudoku[y][x]) && !SUDOKU_IS_SOLVING(sudoku[y][x]))
			{
				sudoku[y][x] |= SUDOKU_FLAG_SOLVING;
				for (u8 n = 1; n < 10; n++)
				{
					if (_set(x, y, n))
					{
						if(_solve())
						{
							return TRUE;
						}
					}
				}
				sudoku[y][x] = 0;
				return FALSE;
			}
		}
	}
	return TRUE;
}
#endif

u8 interpret(char *seq)
{
	switch(seq[0])
	{
	case 'h':
		printf("-- Actions --\n\
			se[t[*[*]]]: Set a number at a given position\n\
			u[n[d[o[*]]]]: Undo last action\n\
			red[o[*]]: Redo last action\n\
			so[l[v[e]]]: Solve the sudoku\n\
			res[e[t]]: Reset current sudoku\n\
			e[x[i[t[*]]]]: Exit the program\n");
		getchar();
		getchar();
		break;
	case 's':
		switch(seq[1])
		{
		case 'e':
			set();
			break;
		case 'o':
			solve();
			break;
		}
		break;
	case 'u':
		undo();
		break;
	case 'r':
		if (seq[1] == 'e')
		{
			switch(seq[2])
			{
			case 's':
				reset();
				break;
			case 'd':
				redo();
				break;
			}
		}
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
	generate: do {
		_clear();
		for (u8 y = 0; y < 9; y++)
		{
			for (u8 x = 0; x < 9; x++)
			{
				if (((u32)rand() % 100) < filled)
				{
					DLOG("waiting\n");
					for (u8 i = 1; i < 10; i++)
					{
						if (check(x, y, i))
						{
							goto possible;
						}
					}
					goto generate;
					possible: while (!check(x, y, r = ((u8)rand() % 9) + 1));
					#ifdef DEBUG
					printf("%d is placable!\n", r);
					#endif
					sudoku[y][x] = r | SUDOKU_FLAG_PREDEFINED;
				}
			}
		}
	}
	#ifdef DEBUG
	while(!_solve(0));
	#else
	while(!_solve());
	#endif
	reset();
	DLOG("done init\n");
}

void _clear()
{
	for (u8 y = 0; y < 9; y++)
	{
		for (u8 x = 0; x < 9; x++)
		{
			sudoku[y][x] = 0;
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
		if (check_win())
		{
			printf("SUDOKU SOLVED! CONGRATULATIONS!");
			break;
		}
		// Abfrage von Aktion
		printf("Action: ");
		scanf("%5s", action);
		if (!interpret(action)) break;
	}
	return 0;
}