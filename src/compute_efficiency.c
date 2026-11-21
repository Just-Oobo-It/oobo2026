#include "compute_efficiency.h"
#include <stdlib.h>

int *compute_efficiency(
    int temperature,
    int sunshine,
    int humidity,
    int clouds,
    int wind,
    int rain,
    int soil_fertility,
    int forest,
    int seismic_activity,
    int water)
{
    int *res;

    res = (int *)calloc(sizeof(int), 5);
    
    res[SOLAR] = compute_solar(temperature, sunshine, humidity, clouds, rain);
    res[WIND] = compute_wind(wind, rain);
    res[HYDRO] = compute_hydro(water, rain, temperature);
    res[GEO] = compute_geo(seismic_activity);
    res[BIO] = compute_bio(forest, soil_fertility);

    return (res);
}

int compute_solar(
    int temperature,
    int sunshine,
    int humidity,
    int clouds,
    int rain)
{
    int res;

    res = 100;
    if (sunshine < 50)
        res = (res*sunshine) / 100;
    if (clouds > 30)
        res = (res * (100 - clouds)) / 100;
    if (humidity > 60)
        res *= 0.5;
    res = (res * rain) / 100;
    if (temperature < -20 || temperature > 60)
        res = res / 4;
}

int compute_wind(int wind,
                 int rain)
{
}

int compute_hydro(int water,
                  int rain,
                  int temperature)
{
}

int compute_geo(int seismic_activity)
{
}

int compute_bio(int forest,
                int soil_fertility)
{
}
