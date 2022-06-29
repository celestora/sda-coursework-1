#ifndef COURSEWORK_GENERATORS_H
#define COURSEWORK_GENERATORS_H
#include <stdlib.h>
#include <time.h>

typedef unsigned int(*Generator)(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int ordered(unsigned int perv, unsigned P, unsigned M, unsigned N);
unsigned int backordered(unsigned int perv, unsigned P, unsigned M, unsigned N);
unsigned int randomized(unsigned int perv, unsigned P, unsigned M, unsigned N);

#endif //COURSEWORK_GENERATORS_H
