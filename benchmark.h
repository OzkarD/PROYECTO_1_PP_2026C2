#pragma once
#include "config.h"

typedef void (*Sorting_Method)(int* v, int n);

ResultTime benchmarkSortingMethod(Sorting_Method method, const int* v, int size, int repetitions);

void printBenchmarkTable(ResultTime& seq_bitonic, ResultTime& par_bitonic,
						ResultTime& seq_bubble, ResultTime& par_bubble,
						ResultTime& seq_insertion, ResultTime& par_insertion,
						ResultTime& seq_merge, ResultTime& par_merge,
						ResultTime& seq_quick, ResultTime& par_quick,
						ResultTime& seq_selection, ResultTime& par_selection);