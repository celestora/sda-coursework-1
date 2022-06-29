#include "Generators.h"

unsigned int ordered(unsigned int perv, unsigned P, unsigned M, unsigned N) {
    return perv + 1;
}

unsigned int backordered(unsigned int perv, unsigned P, unsigned M, unsigned N) {
    if(perv == 0)
        return P * M * N;

    return perv - 1;
}

unsigned int randomized(unsigned int perv, unsigned P, unsigned M, unsigned N) {
    unsigned int max = P*M*N;
    
    return rand() % (max + 1);
}
