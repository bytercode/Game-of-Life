#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curses.h>
#include <time.h>
#include "toroidal_array.h"
#include "GoL.h"

#if defined(__unix__) || defined(__APPLE__)
#define CLEAR() system("clear")
#elif defined(__WIN32__) || defined(__MINGW32__) || defined(WIN32)
#define CLEAR() system("cls")
#else
#define CLEAR() puts("UNSUPPORTTED CLEABRHRHRHBFJF")
#endif

#define TOLOWER(chr) (chr >= 'A' && chr <= 'Z' ? chr + 32 : chr)

void cgol_print(const conwaysgol_t *cgol, wchar_t t, wchar_t f)
{
	for (ssize_t y = 0; y < cgol->toroidal_array.height; ++y)
	{
		for (ssize_t x = 0; x < cgol->toroidal_array.width; ++x)
			putwchar(cgol_sgetat(cgol, x, y) ? t : f);

		putchar(0xa);
	}
}

int main(void)
{
	conwaysgol_t gol;
	cgol_init(&gol, 10, 10);
	cgol_resize(&gol, 50, 59, 0);

	gol.survive_rules = CGOL_PDSR_MAZE;
	gol.born_rules = CGOL_PDBR_MAZE;
	//cgol_ssetat(&gol, 1, 50/2, 59/2);
	cgol_ssetat(&gol, 1, 1, 0);
	cgol_ssetat(&gol, 1, 0, 1);
	cgol_ssetat(&gol, 1, 0, 2);
	cgol_ssetat(&gol, 1, 1, 2);
	cgol_ssetat(&gol, 1, 2, 2);

	/*
	// First Rectangle
	cgol_ssetat(&gol, 1, 0, 4);
	cgol_ssetat(&gol, 1, 1, 4);
	cgol_ssetat(&gol, 1, 0, 5);
	cgol_ssetat(&gol, 1, 1, 5);

	// The circle in the middle
	cgol_ssetat(&gol, 1, 10, 4);
	cgol_ssetat(&gol, 1, 10, 5);
	cgol_ssetat(&gol, 1, 10, 6);

	cgol_ssetat(&gol, 1, 11, 3);
	cgol_ssetat(&gol, 1, 11, 7);

	cgol_ssetat(&gol, 1, 12, 2);
	cgol_ssetat(&gol, 1, 12, 8);

	cgol_ssetat(&gol, 1, 13, 2);
	cgol_ssetat(&gol, 1, 13, 8);

	cgol_ssetat(&gol, 1, 14, 5);

	cgol_ssetat(&gol, 1, 15, 3);
	cgol_ssetat(&gol, 1, 15, 7);

	cgol_ssetat(&gol, 1, 16, 4);
	cgol_ssetat(&gol, 1, 16, 5);
	cgol_ssetat(&gol, 1, 16, 6);

	cgol_ssetat(&gol, 1, 17, 5);

	// ,The 3x2 rectangle
	cgol_ssetat(&gol, 1, 20, 2);
	cgol_ssetat(&gol, 1, 20, 3);
	cgol_ssetat(&gol, 1, 20, 4);

	cgol_ssetat(&gol, 1, 21, 2);
	cgol_ssetat(&gol, 1, 21, 3);
	cgol_ssetat(&gol, 1, 21, 4);

	// The 3 rows behind the 3x2 rect
	cgol_ssetat(&gol, 1, 22, 1);
	cgol_ssetat(&gol, 1, 22, 5);

	cgol_ssetat(&gol, 1, 24, 1);
	cgol_ssetat(&gol, 1, 24, 5);
	cgol_ssetat(&gol, 1, 24, 0);
	cgol_ssetat(&gol, 1, 24, 6);

	// The last rectangle
	cgol_ssetat(&gol, 1, 34, 2);
	cgol_ssetat(&gol, 1, 34, 3);

	cgol_ssetat(&gol, 1, 35, 2);
	cgol_ssetat(&gol, 1, 35, 3);*/

	wchar_t yes = L'\u2b1c', no = L'\u2b1b';
	unsigned gen = 0;
	while (1)
	{
		//CLEAR();
		cgol_print(&gol, yes, no);
		cgol_next_generation(&gol);
		for (ssize_t i = 0; i < CLOCKS_PER_SEC; ++i);
		/*if (++gen == 1000)
			break;*/
	}
/*	int that = getch();
	endwin();
	ta2d_destroy(&mine);*/
	return 0;
}
