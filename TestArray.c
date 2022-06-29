#include "TestArray.h"

TestArray ta_new(Generator seed, unsigned int P, unsigned int M, unsigned int N) {
    unsigned int perv = 0;
    TestArray arr = calloc(P, sizeof(unsigned int**));
    for(unsigned int p = 0; p < P; p++) {
        arr[p] = calloc(M, sizeof(unsigned int*));
        for(unsigned int m = 0; m < M; m++) {
            arr[p][m] = calloc(N, sizeof(unsigned int));
            if(arr[p][m] == NULL) {
                if(errno == ENOMEM)
                    fprintf(stderr, "E: Not enough memory to create array!\n");
                else
                    fprintf(stderr, "E: Failed to allocate %zu bytes: Fault %d\n", N * sizeof(unsigned int), errno);

                abort();
            }

            for(unsigned int n = 0; n < N; n++) {
                perv = seed(perv, P, M, N);
                arr[p][m][n] = perv;
            }
        }
    }

    return arr;
}

void ta_describe(TestArray arr, unsigned int P, unsigned int M, unsigned int N) {
    for(unsigned int p = 0; p < P; p++) {
        printf("===\nIncision №%d out of %d:\n\n", p + 1, P);

        for(unsigned int m = 0; m < M; m++) {
            for(unsigned int n = 0; n < N; n++) {
                printf("%d", arr[p][m][n]);
                printf(n == N - 1 ? ";" : ", ");
            }

            printf("\n");
        }

        printf("\nSum:\n");
        for(int n = 0; n < N; n++) {
            unsigned int sum = 0;
            for(int m = 0; m < M; m++)
                sum += arr[p][m][n];

            printf("%d", sum);
            printf(n == N - 1 ? ";\n===\n\n" : ", ");
        }
    }
}

void ta_destroy(TestArray* arr, unsigned int P, unsigned int M, unsigned int N) {
    for(unsigned int p = 0; p < P; p++) {
        for(unsigned int m = 0; m < M; m++)
            free((*arr)[p][m]);

        free((*arr)[p]);
    }

    free(*arr);
    *arr = NULL;
}