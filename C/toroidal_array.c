#include "toroidal_array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TA2D_INDEX_2D_ARRAY(arrayptr, x, y, h, elemsize) (arrayptr + elemsize * (y + x * h))

/*
ssize_t eucmod(ssize_t opx, ssize_t opy)
{
	ssize_t rslt = opx % opy;
	if ((rslt > 0 && opy < 0) || (rslt < 0 && opy > 0))
		rslt += opy;

	return rslt;
}*/

ssize_t eucmod(ssize_t a, ssize_t base)
{
	 return (a < 0 ? ((a % base) + base) % base : a % base);
}

int ta2d_init(toroidal_array_2d_t *ta2d, size_t type_size, ssize_t width, ssize_t height, void *fill)
{
	if (width < 0 || height < 0)
		return -1;

	size_t total_array_length = type_size * (width * height);
	if ((ta2d->array = malloc(total_array_length)) == NULL)
		return -2;

	ta2d->type_size = type_size;
	ta2d->width = width;
	ta2d->height = height;
	if (fill) ta2d_fill(ta2d, fill);

	return 0;
}

int ta2d_resize(toroidal_array_2d_t *ta2d, ssize_t new_width, ssize_t new_height, void *fill)
{
	if (new_width < 0 || new_height < 0)
		return -1;

	void *new_array = malloc(new_width * new_height);
	if (new_array == NULL)
		return -2;

	ssize_t copied_width = new_width < ta2d->width ? new_width : ta2d->width;
	ssize_t copied_height = new_height < ta2d->height ? new_height : ta2d->height;
	for (ssize_t y = 0; y < copied_height; ++y)
		for (ssize_t x = 0; x < copied_width; ++x)
			memcpy(TA2D_INDEX_2D_ARRAY(new_array, x, y, new_height, ta2d->type_size), TA2D_INDEX_2D_ARRAY(ta2d->array, x, y, ta2d->height, ta2d->type_size), ta2d->type_size);

	if (fill != NULL)
	{
		for (; copied_height < new_height; ++copied_height)
			for (ssize_t x = 0; x < new_width; ++x)
				memcpy(TA2D_INDEX_2D_ARRAY(new_array, x, copied_height, new_height, ta2d->type_size), fill, ta2d->type_size);

		for (; copied_width < new_width; ++copied_width)
			for (ssize_t y = 0; y < new_height; ++y)
				memcpy(TA2D_INDEX_2D_ARRAY(new_array, copied_width, y, new_height, ta2d->type_size), fill, ta2d->type_size);
	}

	ta2d->width = new_width;
	ta2d->height = new_height;
	free(ta2d->array);
	ta2d->array = new_array;
	return 0;
}

void *ta2d_getat(const toroidal_array_2d_t *ta2d, ssize_t x, ssize_t y)
{
	// TA2D_INDEX_2D_ARRAY()
	return TA2D_INDEX_2D_ARRAY(ta2d->array, eucmod(x, ta2d->width), eucmod(y, ta2d->height), ta2d->height, ta2d->type_size);
}

void ta2d_setat(toroidal_array_2d_t *ta2d, const void *buffer, ssize_t x, ssize_t y)
{
	memcpy(TA2D_INDEX_2D_ARRAY(ta2d->array, eucmod(x, ta2d->width), eucmod(y, ta2d->height), ta2d->height, ta2d->type_size), buffer, ta2d->type_size);
}

void ta2d_fill(toroidal_array_2d_t *ta2d, void *fill)
{
	size_t total_array_length = ta2d->type_size * (ta2d->width * ta2d->height);
	for (size_t i = 0; i < total_array_length; ++i)
		memcpy(ta2d->array + (i * ta2d->type_size), fill, ta2d->type_size);
}

int ta2d_copy(toroidal_array_2d_t *ta2d, const toroidal_array_2d_t *cpfrom)
{
	return ta2d_init(ta2d, cpfrom->type_size, cpfrom->width, cpfrom->height, NULL);
}

int ta2d_copyall(toroidal_array_2d_t *ta2d, const toroidal_array_2d_t *cpfrom)
{
	int rv = ta2d_init(ta2d, cpfrom->type_size, cpfrom->width, cpfrom->height, NULL);
	if (rv != 0)
		return rv;

	memcpy(ta2d->array, cpfrom->array, cpfrom->type_size*(cpfrom->width * cpfrom->height));
	return 0;
}

void ta2d_destroy(toroidal_array_2d_t *ta2d)
{
	free(ta2d->array);
}

#undef TA2D_INDEX_2D_ARRAY
