#include "compute_efficiency.h"
#include <stdlib.h>

int keep_btwn_100(int x)
{
    if (x > 100)
        return 100;
    if (x < 0)
        return 0;
    return x;
}

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

    res = keep_btwn_100(sunshine * 2);
    res = (res * (100 - ((rain * 2) - (clouds * 3)) / 10)) / 100; // rain * 0.2, clouds *0.3
    if (humidity > 80) // too much humidity lowers efficiency
        res = res * 9 / 10;
    if (humidity > 90) // too much humidity lowers efficiency (encore)
        res = res * 9 / 10;
    if (temperature > 25) // trop cho => 0.4% par degré
        res = res * (100 - (((temperature - 25) * 4) / 10)) / 100;
    if (temperature < -10) // trop froi => 80% 
        res = res * 8 / 10;
    return keep_btwn_100(res);
}

int compute_wind(int wind,
                 int rain)
{
    int res;

    res = keep_btwn_100(wind * wind / 40); // jsp mais ça a l'air cohérant en sah
    if (rain > 75) // trop de pluie => corrosion => perte en efficacité, 0.2% for each percent of rain after 75
        res = res - ((rain - 75) * 2 / 10);
    return res;
}

int compute_hydro(int water,
                  int rain,
                  int temperature)
{
    int res;

    res = keep_btwn_100(((water * 8) + (rain * 2)) / 10); // 80% for water, 20% for rain
    if (temperature < -20) // if highly freezing, half by 2
        res = res / 2;
    if (temperature < 0) // if freezing, half by 2 (which makes highly freezing half by 4)
        res = res / 2;
    if (temperature > 25) // when hot temperatures, evaporation of water
        res = res * 9 / 10;
    return res;
}

int compute_geo(int seismic_activity)
{
    return keep_btwn_100(seismic_activity); // jsp gros
}

int compute_bio(int forest,
                int soil_fertility)
{
    return keep_btwn_100((forest * 40 + soil_fertility * 60) / 100); // 40% foret and 60% fertility (le sol hein)
}

// notice : la plupart des chiffres sortent de mon *chapeau* 