#include "compute_efficiency.h"
#include <stdio.h>
#include <stdlib.h>

const char *ENERGY_NAME[5] = {"SOLAR", "WIND", "HYDRO", "GEO", "BIO"};

int main(void)
{
    int temperature = 18;
    int sunshine = 34;
    int humidity = 80;
    int clouds = 70;
    int wind = 45;
    int rain = 55;
    int soil_fertility = 75;
    int forest = 25;
    int seismic_activity = 10;
    int water = 50;
    int *results = compute_efficiency(
        temperature,
        sunshine,
        humidity,
        clouds,
        wind,
        rain,
        soil_fertility,
        forest,
        seismic_activity,
        water);
    
    if (results == NULL)
        return 1;
    printf("Test with european like environment :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s: %d%%\n", ENERGY_NAME[i], results[i]);
    }
    free(results);

    temperature = 28;
    sunshine = 50;
    humidity = 25;
    clouds = 10;
    wind = 40;
    rain = 2;
    soil_fertility = 5;
    forest = 0;
    seismic_activity = 15;
    water = 3;

    results = compute_efficiency(
        temperature,
        sunshine,
        humidity,
        clouds,
        wind,
        rain,
        soil_fertility,
        forest,
        seismic_activity,
        water);
    if (results == NULL)
        return 1;
    printf("\n\nTest with desert like environment :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s: %d%%\n", ENERGY_NAME[i], results[i]);
    }
    free(results);

    return 0;
}