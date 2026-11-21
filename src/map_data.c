#include "map_data.h"

int get_data_at_pixel(int **map, int x, int y)
{
    return (int)((map[y][x] / 255) * 100);
}