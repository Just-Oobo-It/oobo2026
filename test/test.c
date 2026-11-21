#include "compute_efficiency.h"
#include <stdio.h>

const char* ENERGY_NAME[5] = {"SOLAR", "WIND", "HYDRO", "GEO", "BIO"};

int main(void)
{
    int temperature = 26;
    int sunshine = 48;
    int humidity = 20;
    int clouds = 38;
    int wind = 20;
    int rain = 40;
    int soil_fertility = 50;
    int forest = 18;
    int seismic_activity = 2;
    int water = 30;

    int* results = compute_efficiency(
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

    for (int i = 0; i < 5; i++)
    {
        printf("%s: %d%%\n", ENERGY_NAME[i], results[i]);
    }
    return 0;
}