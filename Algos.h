#ifndef COURSEWORK_ALGOS_H
#define COURSEWORK_ALGOS_H
#include <time.h>
#include "TestArray.h"

typedef clock_t (*Algo)(TestArray, unsigned int, unsigned int, unsigned int);

#define BEGIN_ALGO(name) \
    clock_t name(TestArray arr, unsigned int P, unsigned int M, unsigned int N) { \
        clock_t time_start = clock(), time_stop;

#define END_ALGO \
    time_stop = clock(); \
    return time_stop - time_start; \
    }

#define INIT_SUM \
    unsigned int* Sum = calloc(N, sizeof(unsigned int)); \
    for(unsigned int j = 0; j < N; j++) { \
        Sum[j] = 0; \
        for(unsigned int k = 0; k < M; k++) \
            Sum[j] += arr[p][k][j]; \
    }

#define SWAP_ELEMENTS(a, b) \
    unsigned int temp = Sum[a]; \
    Sum[a] = Sum[b]; \
    Sum[b] = temp; \
    for(unsigned int sort_k = 0; sort_k < M; sort_k++) { \
        unsigned int buf  = arr[p][sort_k][a]; \
        arr[p][sort_k][a] = arr[p][sort_k][b]; \
        arr[p][sort_k][b] = buf; \
    }

#define SWAP_ELEMENTS_IF(condition, a, b) \
    if(condition) { \
        SWAP_ELEMENTS(a, b) \
    }

clock_t Select6(TestArray arr, unsigned int P, unsigned int M, unsigned int N);
clock_t Select8(TestArray arr, unsigned int P, unsigned int M, unsigned int N);
clock_t Select3Exchange(TestArray arr, unsigned int P, unsigned int M, unsigned int N);

#endif //COURSEWORK_ALGOS_H
