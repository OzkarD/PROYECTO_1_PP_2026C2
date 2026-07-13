#include "selection_sort.h"
#include "vector_tools.h"
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void sequential::selection_sort(int* v, int n)
{
    cout << "Ejecutando selection sort en secuencial..." << endl;

    for (int i = 0; i < n - 1; i++)
    {
        int value_min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[value_min])
                value_min = j;
        }
        swap(v[i], v[value_min]);
    }
    checkSorted(v, n);
}

void parallel::selection_sort(int* v, int n)
{
    cout << "Ejecutando selection_sort paralelo..." << endl;

    int num_threads = omp_get_max_threads(); // número de hilos disponibles
    vector<int> mins(num_threads);           // arreglo dinámico, uno por hilo

    for (int i = 0; i < n - 1; i++)
    {
        int value_min = i;

#pragma omp parallel
        {
            int tid = omp_get_thread_num();
            int local_min = value_min;

#pragma omp for
            for (int j = i + 1; j < n; j++)
            {
                if (v[j] < v[local_min])
                    local_min = j;
            }

            mins[tid] = local_min;
        }

        for (int t = 0; t < num_threads; t++)
        {
            if (v[mins[t]] < v[value_min])
                value_min = mins[t];
        }

        swap(v[i], v[value_min]);
    }

    checkSorted(v, n);
}

static void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}