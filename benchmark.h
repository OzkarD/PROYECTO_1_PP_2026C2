#pragma once
#include "config.h"

typedef UserData(*Sequencial_Method)(const int* v, int min, int max);
typedef UserData(*Parallel_Method)(const int* v, int min, int max);

ResultTime benchmarkSequencialMethod(Sequencial_Method Method, const int* v, int min, int max, int repetitions);
ResultTime benchmarkParallelMethod(Parallel_Method Method, const int* v, int min, int max, int repetitions);

void printBenchmarkTable(const ResultTime* seqResult, const ResultTime* parResult);