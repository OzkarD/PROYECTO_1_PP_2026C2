#include "bitonic_sort.h"
#include <iostream>
#include <omp.h>

#define UMBRAL 1024

using namespace std;

void sequential::bitonic_sort(int* v, int n) 
{
    cout << "Ejecutando bitonic_sort secuencial..." << endl;
    return;
}
 
void parallel::bitonic_sort(int* v, int n)
{
    cout << "Ejecutando bitonic_sort paralelo..." << endl;

    if (v == nullptr || n <= 1)
        return;

#pragma omp parallel
    {
#pragma omp single
        {
            bitonicSort_parallel(v, 0, n, false);
            // false = descendente
            // true  = ascendente
        }
    }
}

void bitonicSort_parallel(int v[], int low, int count, bool ascending)
{
    if (count <= UMBRAL)
    {
        bitonicSort(v, low, count, ascending);
        return;
    }

        int k = count / 2;

#pragma omp task if(count > UMBRAL)
        {
            bitonicSort_parallel(v, low, k, true);
        }

#pragma omp task if(count > UMBRAL)
        {
            bitonicSort_parallel(v, low + k, k, false);
        }

#pragma omp taskwait

        bitonicMerge_parallel(v, low, count, ascending);

}

void bitonicMerge_parallel(int v[], int low, int count, bool ascending)
{
    if (count <= UMBRAL) 
    {
        bitonicMerge(v, low, count, ascending); 
        return;
    }

        int k = count / 2;

#pragma omp parallel for if(count > UMBRAL)
        for (int i = low; i < low + k; i++)
        {
            compare(v, i, i + k, ascending);
        }

        bitonicMerge_parallel(v, low, k, ascending);
        bitonicMerge_parallel(v, low + k, k, ascending);
}