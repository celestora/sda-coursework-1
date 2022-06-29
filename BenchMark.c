#include "BenchMark.h"
#include "Table.h"

#define ARRSIZE task->size[0], task->size[1], task->size[2]

struct NamedAlgo* na_new(char* name, Algo algo) {
    struct NamedAlgo* res = malloc(sizeof(struct NamedAlgo));
    res->name = name;
    res->algo = algo;

    return res;
}

struct NamedGenerator* ng_new(char* name, Generator generator) {
    struct NamedGenerator* res = malloc(sizeof(struct NamedGenerator));
    res->name      = name;
    res->generator = generator;

    return res;
}

long double priv_bc_time(unsigned int iterations, clock_t* measurements) {
    clock_t buf;

    int L = REJECT, R = iterations - 1;
    int k = REJECT;

    for(int j = 0; j < MINMAX; j++) {
        for(int i = L; i < R; i++) {
            if(measurements[i] > measurements[i + 1]) {
                buf                 = measurements[i];
                measurements[i]     = measurements[i + 1];
                measurements[i + 1] = buf;
            }
        }

        R = k;
        for(int i = R - 1; i >= L; i--) {
            if(measurements[i] > measurements[i + 1]) {
                buf                 = measurements[i];
                measurements[i]     = measurements[i + 1];
                measurements[i + 1] = buf;

                k = i;
            }
        }

        L = k + 1;
    }

    clock_t sum = 0;
    for(int i = REJECT + MINMAX; i < iterations - MINMAX; i++)
        sum += measurements[i];

    return (long double) (sum / (iterations - 2*MINMAX - REJECT));
}

struct Table* measure(struct BenchMarkTask* task) {
    if(task->iterations < 12) {
        fprintf(stderr, "E: Invalid iterations param: at least 12 expected, %d found\n", task->iterations);

        return NULL;
    }

    struct Table* table = tbl_new("Measurements");

    unsigned int seedersCount = ll_size(task->seeders);
    char** firstRow = calloc(seedersCount + 1, sizeof(char*));
    firstRow[0] = "Algo / Seed";
    for(int i = 0; i < seedersCount; i++)
        firstRow[i + 1] = ((struct NamedGenerator*) ll_get(task->seeders, i))->name;

    tbl_append_arr(table, seedersCount + 1, firstRow);

    unsigned int algoCount = ll_size(task->algos);
    for(int i = 0; i < algoCount; i++) {
        struct NamedAlgo* algo = ll_get(task->algos, i);
        char** row = calloc(seedersCount + 1, sizeof(char*));
        row[0]     = algo->name;

        for(int j = 0; j < seedersCount; j++) {
            struct NamedGenerator* seeder = ll_get(task->seeders, j);
            clock_t* measurements = calloc(task->iterations, sizeof(clock_t));
            for(int k = 0; k < task->iterations; k++) {
                TestArray array = ta_new(seeder->generator, ARRSIZE);

                if(k == task->iterations - 1 && task->describe) {
                    printf("Before sort:\n");
                    ta_describe(array, ARRSIZE);

                    measurements[k] = algo->algo(array, ARRSIZE);

                    printf("After sort:\n");
                    ta_describe(array, ARRSIZE);
                } else {
                    measurements[k] = algo->algo(array, ARRSIZE);
                }

                ta_destroy(&array, ARRSIZE);
            }

            char* time = malloc(256);
            sprintf(time, "%Lf%c", priv_bc_time(task->iterations, measurements) * task->multiplier, '\0');
            row[j + 1] = time;
        }

        tbl_append_arr(table, seedersCount + 1, row);
    }

    return table;
}
