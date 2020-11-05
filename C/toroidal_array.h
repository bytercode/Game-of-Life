#ifndef TOROIDAL_ARRAY_H_INCLUDED
#define TOROIDAL_ARRAY_H_INCLUDED
#include <stdio.h>

typedef struct toroidal_array_2d
{
        ssize_t width, height;
        size_t type_size;
        void *array;
} toroidal_array_2d_t;

int ta2d_init(toroidal_array_2d_t *ta2d, size_t type_size, ssize_t width, ssize_t height, void *fill);
int ta2d_resize(toroidal_array_2d_t *ta2d, ssize_t new_width, ssize_t new_height, void *fill);

void ta2d_setat(toroidal_array_2d_t *ta2d, const void *buffer, ssize_t x, ssize_t y);
void *ta2d_getat(const toroidal_array_2d_t *ta2d, ssize_t x, ssize_t y);
void ta2d_fill(toroidal_array_2d_t *ta2d, void *buffer);

int ta2d_copy(toroidal_array_2d_t *ta2d, const toroidal_array_2d_t *cpfrom); // Copy thw structure and initialize the new array but doesnt copy the old array
int ta2d_copyall(toroidal_array_2d_t *ta2d, const toroidal_array_2d_t *cpfrom); // Copy the structure and the array

void ta2d_destroy(toroidal_array_2d_t *ta2d);

#endif // TOROIDAL_ARRAY_H_INCLUDED
