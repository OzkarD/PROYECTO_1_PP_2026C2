/*
PAREJA A CRAGO: Pareja 7 - Gerardo Martínez / Pedro Meza

En este archivo se ha de desarrollar la lógica del benchmark.h y se ha de 
documentar el código de tal forma que como mínimo, se expliquen el funcionamiento de variables, de funciones
y de librerias extra que sean usadas.  

NOTA: Revisar el benchmark.cpp de prácticas pasadas. En general, se incluyen funciones de 
	OMP y Chrono.
*/
#include <iostream>
#include <chrono>
#include <omp.h>
#include "benchmark.h"

ResultTime benchmarkSortingMethod(Sorting_Method Method, const int* v, int size, int repetitions)
{
	ResultTime Tiempo;

	Tiempo.omp_time = 1e100;
	Tiempo.chrono_time = 1e100;

	return Tiempo;
}


void printBenchmarkTable(const ResultTime* seqResult, const ResultTime* parResult)
{
	return;
}
