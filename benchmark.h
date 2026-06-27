#pragma once
#include "config.h"

typedef void (*Sorting_Method)(const int* v, int size);

ResultTime benchmarkSortingMethod(Sorting_Method method, const int* v, int size, int repetitions);

void printBenchmarkTable(const ResultTime* seqResult, const ResultTime* parResult);