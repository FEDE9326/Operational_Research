#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

double uniform(double a, double b, long *seed);
double uniform01(long *seed);
double negexp (double mean, long *seed);
long rnd32(long seed);

#endif // RANDOM_H_INCLUDED
