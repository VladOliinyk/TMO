#ifndef MODEL
#define MODEL

#include <math.h>
#include <cstdlib>

/*
 * The intensity of arrivals of cars.
 *
 * by default:
 *              0.85 cars per hour
 *                 similar to
 *           0.01416 cars per minute
 *
 *   for this we get: 17 / 1200 = 0.01416
 */
#define PROBABILITY_COME 17
#define PROBABILITY_MAX 1200

int poissonRandom(double expectedValue);

void calculate(int k);

int getPost();
int getObsl();
int getOtk();
int getSm_t_obs();
int getT_och1();
int getT_och2();
int getT_och3();

#endif // MODEL

