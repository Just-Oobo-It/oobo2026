#ifndef COMPUTE_EFFICIENCY_H
#define COMPUTE_EFFICIENCY_H

/*******************************************/
/*                                         */
/*   compute_type :                        */
/*                                         */
/*   Each compute_type function returns    */
/*   a value between 0 and 100 being the   */
/*   percentage of efficiency according    */
/*   to the environment inputs             */
/*                                         */
/* * * * * * * * * * * * * * * * * * * * * */
/*                                         */
/*   compute_efficiency :                  */
/*                                         */
/*   compute_efficiency returns an array   */
/*   of the computed values of each        */
/*   energy type, indexed by enum value    */
/*                                         */
/*******************************************/

typedef enum ENERGY_TYPE
{
    SOLAR = 0,
    WIND,
    HYDRO,
    GEO,
    BIO
} energy_type_t; // 0 -> 4

typedef enum ENVIRONMENT_FACTORS
{
    TEMPERATURE = 0,
    SUNSHINE,
    HUMIDITY,
    CLOUDS,
    WIND_FORCE,
    RAIN,
    SOIL_FERTILITY,
    FOREST,
    SEISMIC_ACTIVITY,
    WATER
} environment_factors_t; // 0 -> 9

typedef struct efficiency_response_s
{
    int                     percentage;
    environment_factors_t   issue;
} efficiency_response_t;

#define ENERGY_TYPE_COUNT 5
#define ENVIRONMENT_FACTORS_COUNT 10

efficiency_response_t *compute_efficiency(int temperature,
                        int sunshine,
                        int humidity,
                        int clouds,
                        int wind,
                        int rain,
                        int soil_fertility,
                        int forest,
                        int seismic_activity,
                        int water); // Returns int*[5] where index is enum ENERGY_TYPE

efficiency_response_t compute_solar(
    int temperature,
    int sunshine,
    int humidity,
    int clouds,
    int rain);

efficiency_response_t compute_wind(int wind,
                 int rain);

efficiency_response_t compute_hydro(int water,
                  int rain,
                  int temperature);

efficiency_response_t compute_geo(int seismic_activity);

efficiency_response_t compute_bio(int forest,
                int soil_fertility);

#endif