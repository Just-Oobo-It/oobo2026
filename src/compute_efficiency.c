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
    int wind,
    int temperature,
    int humidity,
    int rain,
    int sunshine,
    int clouds,
    // int soil_fertility,
    int forest,
    int seismic_activity,
    int water)
{
    efficiency_response_t *res;

    res = (efficiency_response_t *)calloc(ENERGY_TYPE_COUNT, sizeof(efficiency_response_t));

    res[SOLAR] = compute_solar(temperature, humidity, rain, sunshine, clouds);
    // res[SOLAR] = (efficiency_response_t){temperature+20, -1};
    res[WIND] = compute_wind(wind, rain);
    res[HYDRO] = compute_hydro(water, temperature, rain);
    res[GEO] = compute_geo(seismic_activity);
    res[BIO] = compute_bio(forest);

    return (res);
}

efficiency_response_t compute_solar(
    int temperature,
    int humidity,
    int rain,
    int sunshine,
    int clouds)
{
    int res;
    int issue = -1;

    res = keep_btwn_100((sunshine * 2));
    res = (res * (100 - ((rain * 2) + (clouds * 3)) / 10)) / 100; // rain * 0.2, clouds *0.3

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
    // trop cho => ~~0.4%~~ -> 1% par degré
    if (temperature > 25)
    {
        issue = TEMPERATURE;
        res = res * (100 - (((temperature - 25) * 10) / 10)) / 100;
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

efficiency_response_t compute_wind(
    int wind,
    int rain)
{
    int res;
    int issue = -1;

    res = keep_btwn_100(wind * wind / 40); // jsp mais ça a l'air cohérant en sah
    // trop de pluie => corrosion => perte en efficacité, 0.2% for each percent of rain after 75
    if (rain > 75)
    {
        res = keep_btwn_100(res - ((rain - 75) * 2 / 10));
        issue = RAIN;
    }
    efficiency_response_t t = {res, issue};
    return t;
}

efficiency_response_t compute_hydro(
    int water,
    int temperature,
    int rain)
{
    int res = 100;
    int issue = -1;

    res = keep_btwn_100(((water * 8) + (rain * 2)) / 10); // 80% for water, 20% for rain
    // if highly freezing, half by 2
    if (temperature < -20)
    {
        issue = TEMPERATURE;
        res = res / 2;
    }
    // if freezing, half by 2 (which makes highly freezing half by 4)
    if (temperature < 0)
    {
        issue = TEMPERATURE;
        res = res / 2;
    }
    // when hot temperatures, evaporation of water
    if (temperature > 30)
    {
        issue = TEMPERATURE;
        res = res * 9 / 10;
    }
    efficiency_response_t t = {res, issue};
    return t;
}

efficiency_response_t compute_geo(int seismic_activity)
{
    efficiency_response_t t = {keep_btwn_100(seismic_activity), SEISMIC_ACTIVITY};
    return t;
}

efficiency_response_t compute_bio(
    int forest)
{
    efficiency_response_t t = {keep_btwn_100((forest)), FOREST};
    // efficiency_response_t t = {-1, TEMPERATURE};
    return t;
}

// notice : la plupart des chiffres sortent de mon *chapeau*
