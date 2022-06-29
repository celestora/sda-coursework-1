#include "Algos.h"

BEGIN_ALGO(Select6)

    for(unsigned int p = 0; p < P; p++) {
        INIT_SUM;

        unsigned int min;
        for(unsigned int i = 0; i < N - 1; i++) {
            min = i;
            for(unsigned int j = i + 1; j < N; j++)
                if(Sum[j] < Sum[min])
                    min = j;

            SWAP_ELEMENTS_IF(min != i, min, i);
        }

        free(Sum);
    }

END_ALGO

BEGIN_ALGO(Select8)

    for(unsigned int p = 0; p < P; p++) {
        INIT_SUM;

        int L = 0, R = N - 1;
        while(L < R) {
            int min = L, max = L;
            for(int i = L + 1; i < R + 1; i++) {
                if(Sum[i] < Sum[min])
                    min = i;
                else if(Sum[i] > Sum[max])
                    max = i;
            }

            SWAP_ELEMENTS_IF(min != L, min, L);

            if(max != R) {
                SWAP_ELEMENTS_IF(max == L, min, R);
                SWAP_ELEMENTS_IF(max != L, max, R);
            }

            L++;
            R--;
        }

        free(Sum);
    }

END_ALGO

BEGIN_ALGO(Select3Exchange)

    for(unsigned int p = 0; p < P; p++) {
        INIT_SUM;

        int L = 0, R = N - 1;
        while(L < R) {
            SWAP_ELEMENTS_IF(Sum[L] > Sum[R], L, R);

            unsigned int min = Sum[L], max = Sum[R];
            for(int i = L + 1; i < R + 1; i++) {
                if(Sum[i] < min) {
                    min = Sum[i];
                    SWAP_ELEMENTS(i, L);
                } else if(Sum[i] > max) {
                    max = Sum[i];
                    SWAP_ELEMENTS(i, R);
                }
            }

            L++;
            R--;
        }

        free(Sum);
    }

END_ALGO
