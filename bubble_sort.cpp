#include "bubble_sort.h"
#include <iostream>
#include <omp.h>
#include <stdbool.h>
#include "vector_tools.h"

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
	checkSorted(v, n);
    return;
}

void parallel::bubble_sort(int* v, int n) 
{
    cout << "Ejecutando bubble_sort paralelo..." << endl;

    bool sorted = false;

    while (!sorted)
    {
        sorted = true;

        //Definimos la separacion del trabajo en pares e impares para que paralel for funcionen adecuadamente
        //Par
#pragma parallel for share(v, sorted)
        for (int i = 1; i < n - 1; i += 2)
        {
            if (v[i] > v[i + 1])
            {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                sorted = false;
            }
        }
        //Impar
#pragma parallel for share(v, sorted)
        for (int i = 0; i < n - 1; i += 2)
        {
            if (v[i] > v[i + 1])
            {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                sorted = false;
            }
        }
    }
	checkSorted(v, n);
    return;
}