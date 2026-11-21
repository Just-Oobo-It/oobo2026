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

efficiency_response_t *compute_efficiency(
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
    efficiency_response_t *res;

    res = (efficiency_response_t *)calloc(sizeof(efficiency_response_t *), ENERGY_TYPE_COUNT);

    res[SOLAR] = compute_solar(temperature, sunshine, humidity, clouds, rain);
    res[WIND] = compute_wind(wind, rain);
    res[HYDRO] = compute_hydro(water, rain, temperature);
    res[GEO] = compute_geo(seismic_activity);
    res[BIO] = compute_bio(forest, soil_fertility);

    return (res);
}

efficiency_response_t compute_solar(
    int temperature,
    int sunshine,
    int humidity,
    int clouds,
    int rain)
{
    int res;
    int issue = -1;
    res = keep_btwn_100(sunshine * 2);
    res = (res * (100 - ((rain * 2) - (clouds * 3)) / 10)) / 100; // rain * 0.2, clouds *0.3
    // too much humidity lowers efficiency
    if (humidity > 50)
    {
        issue = HUMIDITY;
        res = res * 7 / 10;
    }
    // too much humidity lowers efficiency (encore)
    if (humidity > 90)
    {
        issue = HUMIDITY;
        res = res * 9 / 10;
    }
    // trop cho => 0.4% par degré
    if (temperature > 25)
    {
        issue = TEMPERATURE;
        res = res * (100 - (((temperature - 25) * 4) / 10)) / 100;
    }
    // trop froi => 80%
    if (temperature < -10)
    {
        issue = TEMPERATURE;
        res = res * 8 / 10;
    }
    res = keep_btwn_100(res);
    efficiency_response_t t = {res, issue};
    return t;
}

efficiency_response_t compute_wind(int wind,
                                   int rain)
{
    int res;
    int issue = -1;

    res = keep_btwn_100(wind * wind / 40); // jsp mais ça a l'air cohérant en sah
    // trop de pluie => corrosion => perte en efficacité, 0.2% for each percent of rain after 75
    if (rain > 75)
    {
        res = res - ((rain - 75) * 2 / 10);
        issue = RAIN;
    }
    efficiency_response_t t = {res, issue};
    return t;
}

efficiency_response_t compute_hydro(int water,
                                    int rain,
                                    int temperature)
{
    int res;
    int issue = -1;

    res = keep_btwn_100(((water * 8) + (rain * 2)) / 10); // 80% for water, 20% for rain
    // if highly freezing, half by 2
    if (temperature < -20)
    {
        res = res / 2;
    }
    // if freezing, half by 2 (which makes highly freezing half by 4)
    if (temperature < 0)
    {
        res = res / 2;
    }
    // when hot temperatures, evaporation of water
    if (temperature > 25)
    {
        res = res * 9 / 10;
    }
    efficiency_response_t t = {res, issue};
    return t;
}

efficiency_response_t compute_geo(int seismic_activity)
{
    efficiency_response_t t = {keep_btwn_100(seismic_activity), -1};
    return t;
}

efficiency_response_t compute_bio(int forest,
                                  int soil_fertility)
{
    efficiency_response_t t = {keep_btwn_100((forest * 40 + soil_fertility * 60) / 100), TEMPERATURE};
    return t;
}

// notice : la plupart des chiffres sortent de mon *chapeau*