#include "map_data.h"

int get_data_at_pixel(int **map, int x, int y)
{
    return (int)((map[y][x] / 255) * 100);
}

int* get_raw_data_array(int ***maps, int x, int y) // maps should be of size ENVIRONMENT_FACTORS_COUNT, one map for each factor
{
    int *factor_values = (int*)calloc(sizeof(int), ENVIRONMENT_FACTORS_COUNT);
    for (int i = 0; i < ENVIRONMENT_FACTORS_COUNT; i++)
    {
        factor_values[i] = get_data_at_pixel(maps[i], x, y);
    }
    return factor_values;
}

int* get_computed_data(int *factor_values, int x, int y)
{
    int temperature = factor_values[TEMPERATURE];
    int sunshine = factor_values[SUNSHINE];
    int humidity = factor_values[HUMIDITY];
    int clouds = factor_values[CLOUDS];
    int wind = factor_values[WIND];
    int rain = factor_values[RAIN];
    int soil_fertility = factor_values[SOIL_FERTILITY];
    int forest = factor_values[FOREST];
    int seismic_activity = factor_values[SEISMIC_ACTIVITY];
    int water = factor_values[WATER];

    return compute_efficiency(
        temperature,
        sunshine,
        humidity,
        clouds,
        wind,
        rain,
        soil_fertility,
        forest,
        seismic_activity,
        water
    );
}