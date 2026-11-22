#include "map_data.h"
#include "compute_efficiency.h"
#include "config.h"
#include "qprint.h"

int get_data_at_pixel(int *map, int x, int y)
{
    return (int)((map[y * WIDTH + x] * 100 / 255));
}

// maps should be of size ENVIRONMENT_FACTORS_COUNT, one map for each factor
int *get_raw_data_array(int **maps, int x, int y)
{
    int *factor_values = (int *)calloc(ENVIRONMENT_FACTORS_COUNT, sizeof(int));
    for (int i = 0; i < ENVIRONMENT_FACTORS_COUNT; i++)
    {
        factor_values[i] = get_data_at_pixel(maps[i], x, y);
    }
    return factor_values;
}

efficiency_response_t *get_computed_data(int **maps, int x, int y)
{
    int *factor_values = get_raw_data_array(maps, x, y);
/*
	Comment : QuarkUp

	attention temperature de 0 à 100 va de ~ -20C à 50C
*/

    int wind = factor_values[WIND_FORCE];
    int temperature = factor_values[TEMPERATURE];
	// qvald(temperature);
	temperature *= 7;
	temperature /= 10;
	temperature -= 20;
    int humidity = factor_values[HUMIDITY];
    int rain = factor_values[RAIN];
    // int sunshine = factor_values[SUNSHINE];
    // int clouds = factor_values[CLOUDS];
    // int soil_fertility = factor_values[SOIL_FERTILITY];
    // int forest = factor_values[FOREST];
    // int seismic_activity = factor_values[SEISMIC_ACTIVITY];
    // int water = factor_values[WATER];

    return compute_efficiency(
        wind,
        temperature,
        humidity,
        rain
        // sunshine,
        // clouds,
        // soil_fertility,
        // forest,
        // seismic_activity,
        // water
	);
}
