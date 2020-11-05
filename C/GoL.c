#include "GoL.h"
#include <stdlib.h>
#include <stdio.h>

#define CGOL_INDEX_2D_ARRAY(arrayptr, x, y, h, elemsize) (arrayptr + elemsize * (y + x * h))

int cgol_init(conwaysgol_t *cgol, ssize_t width, ssize_t height)
{
	int rv;
	char fill = 0;
	if ((rv = ta2d_init(&cgol->toroidal_array, 1, width, height, &fill)) != 0)
		return rv;

	cgol->survive_rules = CGOL_PDSR_CONWAYS_LIFE;
	cgol->born_rules = CGOL_PDBR_CONWAYS_LIFE;
	cgol->wrap = 1;
	return 0;
}

int cgol_resize(conwaysgol_t *cgol, ssize_t new_width, ssize_t new_height, char fill)
{
	return ta2d_resize(&cgol->toroidal_array, new_width, new_height, &fill);
}

void cgol_ssetat(conwaysgol_t *cgol, char setchr, ssize_t x, ssize_t y)
{
	if (cgol->wrap)
		ta2d_setat(&cgol->toroidal_array, &setchr, x, y);
	else if ((x >= 0 && x < cgol->toroidal_array.width) && (y >= 0 && y < cgol->toroidal_array.height))
		*((char*)CGOL_INDEX_2D_ARRAY(cgol->toroidal_array.array, x, y, cgol->toroidal_array.height, cgol->toroidal_array.type_size)) = setchr;
}

char cgol_sgetat(const conwaysgol_t *cgol, ssize_t x, ssize_t y)
{
	if (cgol->wrap)
		return *(char*)ta2d_getat(&cgol->toroidal_array, x, y);
	else if ((x >= 0 && x < cgol->toroidal_array.width) && (y >= 0 && y < cgol->toroidal_array.height))
		return *(char*)CGOL_INDEX_2D_ARRAY(cgol->toroidal_array.array, x, y, cgol->toroidal_array.height, cgol->toroidal_array.type_size);

	return 0;
}

unsigned cgol_get_alive_count_at(const conwaysgol_t *cgol, ssize_t x, ssize_t y)
{
	unsigned count = 0;
	for (int yoff = -1; yoff < 2; ++yoff)
		for (int xoff = -1; xoff < 2; ++xoff)
			count += !!cgol_sgetat(cgol, x + xoff, y + yoff);

	return count;
}

char cgol_determine_next_state_at(const conwaysgol_t *cgol, ssize_t x, ssize_t y)
{
	unsigned alive_count = cgol_get_alive_count_at(cgol, x, y);
	// printf("AC AT (%lld, %lld) IS %u\n", x, y, alive_count);
	if (alive_count == 0)
		return 0;

	if (cgol_sgetat(cgol, x, y))
		return !!(cgol->survive_rules & (1 << (alive_count-1)));

	return !!(cgol->born_rules & (1 << alive_count));
}

char cgol_next_generation_at(conwaysgol_t *cgol, ssize_t x, ssize_t y)
{
	char next_state = cgol_determine_next_state_at(cgol, x, y);
	cgol_ssetat(cgol, next_state, x, y);
	return next_state;
}

int cgol_get_next_generation_ta2d(const conwaysgol_t *cgol, toroidal_array_2d_t *buf)
{
	int rv = ta2d_copy(buf, &cgol->toroidal_array);
	if (rv != 0)
		return rv;

	for (ssize_t y = 0; y < buf->height; ++y)
	{
		for (ssize_t x = 0; x < buf->width; ++x)
		{
			/*
			char next_state = cgol_determine_next_state_at(cgol, x, y);
			if (cgol->wrap)
				ta2d_setat(buf, &next_state, x, y);
			else if ((x >= 0 && x < cgol->toroidal_array.width) && (y >= 0 && y < cgol->toroidal_array.height))
				*((char*)CGOL_INDEX_2D_ARRAY(buf->array, x, y, cgol->toroidal_array.height, cgol->toroidal_array.type_size)) = next_state;*/
			*((char*)CGOL_INDEX_2D_ARRAY(buf->array, x, y, cgol->toroidal_array.height, cgol->toroidal_array.type_size)) = cgol_determine_next_state_at(cgol, x, y);
		}
	}

	return 0;
}

int cgol_next_generation(conwaysgol_t *cgol)
{
	toroidal_array_2d_t next_generation;
	int rv = cgol_get_next_generation_ta2d(cgol, &next_generation);
	if (rv != 0)
		return rv;

	ta2d_destroy(&cgol->toroidal_array);
	cgol->toroidal_array = next_generation;
	return 0;
}

int cgol_add_rule_to_int(enum cgol_rules rule, int theint)
{
	return theint | (int)rule;
}

int cgol_remove_rule_from_int(enum cgol_rules rule, int theint)
{
	return theint & ~(int)rule;
}

int cgol_rule_contains(int theint, enum cgol_rules rule)
{
	return !!(theint & (int)rule);
}

void cgol_destroy(conwaysgol_t *cgol)
{
	ta2d_destroy(&cgol->toroidal_array);
}

#undef CGOL_INDEX_2D_ARRAY
