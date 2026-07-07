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

#include <omp.h>


int main()
{
	srand((unsigned)time(NULL));
	//UserData data = getUserData();

	const int N = 1<<10;
	int* vector = createVector(N);
	fillRandom(vector, N,0, 50);
	printSample(vector, N, 20);

	int* vector_copy = createVector(N);

	copyVector(vector, vector_copy, N);

	double time1 = omp_get_wtime();

	sequential::insertion_sort(vector, N);

	double time2 = omp_get_wtime();

	printf("Tiempo de ejecución secuencial: %f segundos\n", time2 - time1);

	time1 = omp_get_wtime();

	parallel::merge_sort(vector_copy, 0, N - 1, 5);

    time2 = omp_get_wtime();

	printf("Tiempo de ejecución paralelo: %f segundos\n", time2 - time1);

	for (int i = 0; i < N; i++)
	{
		printf("%d ", vector[i]);
	}

	printf("\n");


	for (int i = 0; i < N; i++)
	{
		printf("%d ", vector_copy[i]);
	}

	destroyVector(vector);
	destroyVector(vector_copy);

	return 0;
}

