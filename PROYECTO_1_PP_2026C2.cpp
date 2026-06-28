// PROYECTO_1_PP_2026C2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <time.h>

#include "config.h"
#include "vector_tools.h"
#include "benchmark.h"
#include "metrics.h"

#include "bitonic_sort.h"
#include "bubble_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"


int main() 
{
	srand((unsigned)time(NULL));
	UserData data = getUserData();

	const int N = 1 << data.bit_shift;
	int* vector = createVector(N);
	fillRandom(vector, N, data.min_value, data.max_value);
	printSample(vector, N, 10);
	
	int* vector_copy = createVector(N);// El vector original no se toca, para que cada algoritmo pueda ordenar y no modifique el vector original

	copyVector(vector, vector_copy, N);
	ResultTime seq_bitonic = benchmarkSortingMethod(sequential::bitonic_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime par_bitonic = benchmarkSortingMethod(parallel::bitonic_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime seq_bubble = benchmarkSortingMethod(sequential::bubble_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime par_bubble = benchmarkSortingMethod(parallel::bubble_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime seq_insertion = benchmarkSortingMethod(sequential::insertion_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime par_insertion = benchmarkSortingMethod(parallel::insertion_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime seq_merge = benchmarkSortingMethod(sequential::merge_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime par_merge = benchmarkSortingMethod(parallel::merge_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime seq_quick = benchmarkSortingMethod(sequential::quick_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime par_quick = benchmarkSortingMethod(parallel::quick_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime seq_selection = benchmarkSortingMethod(sequential::selection_sort, vector_copy, data.repetitions);
	copyVector(vector, vector_copy, N);
	ResultTime par_selection = benchmarkSortingMethod(parallel::selection_sort, vector_copy, data.repetitions);

	printBenchmarkTable(seq_bitonic, par_bitonic,
						seq_bubble, par_bubble,
						seq_insertion, par_insertion,
						seq_merge, par_merge,
						seq_quick, par_quick,
						seq_selection, par_selection);
	
	printTheoreticalMetrics(N);
	printAssignmentReminder();

	destroyVector(vector);
	destroyVector(vector_copy);
	return 0;
}

