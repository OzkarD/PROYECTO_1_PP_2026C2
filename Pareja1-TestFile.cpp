//--------------------------
//Esto fue generado por la pareja responsable del algoritmo
#include "bubble_sort.h"
//#include "bubble_sort.cpp"
#include <iostream>
//--------------------------
//Esto fue generado por la pareja responsable del algoritmo
#include<omp.h>
#define UMBRAL 65536 //Evita crear demasiadas para arreglos pequeños.
#include"bitonic_sort.h"
//--------------------------


#include <stdlib.h> //Implementado por integrador
#include <time.h>//Implementado por integrador
#include <time.h>//Implementado por integrador



using namespace std;

void sequential::bubble_sort(int* v, int n) 
{
    cout << "Ejecutando bubble_sort secuencial..." << endl;
    
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    return;
}

//Implementado por el integrador
/*
int main(void)
{
    srand(time(NULL));

    int size = 100000;
    //int array[1e8] = {0};

    int* array = new int[size];

    for(int i = 0; i < 20; i++)
    {
        array[i] = rand();
        printf("%d ", array[i]);
    }
    printf("\n");

    sequential::bubble_sort(array, size);

    for(int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    delete[] array;
}
*/

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//A partir de aquí se revisa el paralel bitonic sort generado por la pareja 1.

void swap_int(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void compare(int v[], int i, int j, bool ascending)
{
    if (ascending)
    {
        if (v[i] > v[j])
            swap_int(&v[i], &v[j]);
    }
    else
    {
        if (v[i] < v[j])
            swap_int(&v[i], &v[j]);
    }
}

void bitonicMerge(int v[], int low, int count, bool ascending)
{
    if (count > 1)
    {
        int k = count / 2;

        for (int i = low; i < low + k; i++)
            compare(v, i, i + k, ascending);

        bitonicMerge(v, low, k, ascending);
        bitonicMerge(v, low + k, k, ascending);
    }
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


void bitonicSort(int v[], int low, int count, bool ascending)
{
    if (count > 1)
    {
        int k = count / 2;

        // Primera mitad ascendente
        bitonicSort(v, low, k, true);

        // Segunda mitad descendente
        bitonicSort(v, low + k, k, false);

        // Mezclar
        bitonicMerge(v, low, count, ascending);
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

void printArray(int v[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");
}

int nextPowerOfTwo(int n)
{
    if (n <= 1)
        return 1;

    int p = 1;

    while (p < n)
        p <<= 1;

    return p;
}

// Aquí se define la función 
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

//Implementado por el integrador

int main(void)
{
    srand(time(NULL));

    int size = nextPowerOfTwo(1e8);
    //int array[1e8] = {0};

    int* array = new int[size];

    for(int i = 0; i < size; i++)
    {
        array[i] = rand();
    }
    printf("\n");

    parallel::bitonic_sort(array, size);

    for(int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    delete[] array;
}
