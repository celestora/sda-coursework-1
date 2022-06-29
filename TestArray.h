#ifndef COURSEWORK_TESTARRAY_H
#define COURSEWORK_TESTARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "Generators.h"

typedef unsigned int*** TestArray;

TestArray ta_new(Generator seed, unsigned P, unsigned M, unsigned N);
void ta_describe(TestArray arr, unsigned P, unsigned M, unsigned N);
void ta_destroy(TestArray* arr, unsigned P, unsigned M, unsigned N);

#endif //COURSEWORK_TESTARRAY_H