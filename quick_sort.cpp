#include "quick_sort.h"
#include <iostream>
#include "vector_tools.h"
#include <omp.h>

using namespace std;

// Función auxiliar para intercambiar dos elementos
static void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Función auxiliar para particionar el arreglo
static int partition(int* v, int low, int high)
{
    int pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (v[j] <= pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[high]);

    return i + 1;
}

// Función recursiva de Quick Sort
static void quickSortRecursive(int* v, int low, int high)
{
    if (low < high)
    {
        int pi = partition(v, low, high);

        quickSortRecursive(v, low, pi - 1);
        quickSortRecursive(v, pi + 1, high);
    }
}

void sequential::quick_sort(int* v, int n)
{
    if (v == nullptr || n <= 1)
        return;
    cout << "Ejecutando quick_sort secuencial..." << endl;
    quickSortRecursive(v, 0, n - 1);
	checkSorted(v, n);
}

void parallel::quick_sort(int* v, int n)
{
    if (v == nullptr || n <= 1)
        return;
    cout << "Ejecutando quick_sort paralelo..." << endl;

    int pi = partition(v, 0, n - 1);

#pragma omp parallel for shared(v)
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            // Primer hilo
            quickSortRecursive(v, 0, pi - 1);
        }
        else
        {
            // Segundo hilo
            quickSortRecursive(v, pi + 1, n - 1);
        }
    }
    checkSorted(v, n);
}