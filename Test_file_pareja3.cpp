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

//Implementado por el Integrador
#include "vector_tools.cpp"
#include "insertion_sort.cpp"
#include "merge_sort.cpp"

/*
int main()
{
	srand((unsigned)time(NULL));
	//UserData data = getUserData();

	const int N = 50000;
	int* vector = createVector(N);
	fillRandom(vector, N,-50, 50);
	printSample(vector, N, 20);

	sequential::insertion_sort(vector, N);

	for (int i = 0; i < 20; i++)
	{
		printf("%d ", vector[i]);
	}

	destroyVector(vector);

	return 0;
}
*/


int main()
{
	srand((unsigned)time(NULL));
	//UserData data = getUserData();

	const int N = 1e8;
	int* vector = createVector(N);
	fillRandom(vector, N,-50, 50);
	printSample(vector, N, 20);

	parallel::merge_sort(vector, N);

	for (int i = 0; i < 20; i++)
	{
		printf("%d ", vector[i]);
	}

	destroyVector(vector);

	return 0;
}
