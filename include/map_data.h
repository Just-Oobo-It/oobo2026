#ifndef MAP_DATA_H
#define MAP_DATA_H

#include "compute_efficiency.h"
#include <stdlib.h>

int get_data_at_pixel(int **map, int x, int y);

int *get_computed_data_array(int ***maps, int x, int y);

int* get_computed_data(int *factor_values, int x, int y)

#endif