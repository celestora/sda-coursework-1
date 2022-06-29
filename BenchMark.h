#ifndef COURSEWORK_BENCHMARK_H
#define COURSEWORK_BENCHMARK_H
#include "LinkedList.h"
#include "Algos.h"

#define REJECT 2.0
#define MINMAX 3.0

#define SETSIZE(var, p, m, n) \
    var = calloc(3, sizeof(unsigned int)); \
    var[0] = p; \
    var[1] = m; \
    var[2] = n;

struct NamedAlgo {
    char* name;
    Algo algo;
};

struct NamedGenerator {
    char* name;
    Generator generator;
};

struct BenchMarkTask {
    struct LinkedList* algos;   // LinkedList<NamedAlgo>
    struct LinkedList* seeders; // LinkedList<NamedGenerator>
    unsigned int multiplier;    // Multiply calculated time by N times
    unsigned int iterations;    // Execute measurements N times
    unsigned int* size;         // {P, M, N} array
    bool describe;              // Call ta_describe() before and after sort?
};

struct NamedAlgo* na_new(char* name, Algo algo);
struct NamedGenerator* ng_new(char* name, Generator generator);
#define ALGO(name) na_new(#name, &name)
#define SEED(name) ng_new(#name, &name)

struct Table* measure(struct BenchMarkTask* task);

#endif //COURSEWORK_BENCHMARK_H