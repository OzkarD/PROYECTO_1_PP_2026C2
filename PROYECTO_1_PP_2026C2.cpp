// PROYECTO_1_PP_2026C2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <time.h>

#include "config.h"
#include "vector_tools.h"

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

	//copyVector(vector, vector_copy, N);

	/*
	Implementacion de las funciones con benchmark
	*/

	/*
	Impresion del benchmark
	*/

	/*
	Impresion de metrics
	*/

	destroyVector(vector);
	return 0;
}

