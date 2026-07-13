#include <iostream>
<<<<<<< HEAD
#include <omp.h>

#define UMBRAL 1024
=======
#include <limits>
#include <vector>
#include "bitonic_sort.h"
#include "vector_tools.h"
>>>>>>> Integrador_Jhon

using namespace std;

// Intercambia dos elementos
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Calcula la siguiente potencia de 2
int nextPowerOfTwo(int n)
{
    if (n <= 1)
        return 1;

    int p = 1;

    while (p < n)
        p <<= 1;

    return p;
}

// Compara e intercambia según el orden
void compare(int v[], int i, int j, bool ascending)
{
    if (ascending)
    {
        if (v[i] > v[j])
            swap(&v[i], &v[j]);
    }
    else
    {
        if (v[i] < v[j])
            swap(&v[i], &v[j]);
    }
}

// Mezcla bitónica
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

// Ordenamiento recursivo
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

// Función solicitada
void sequential::bitonic_sort(int* v, int n)
{
    cout << "Ejecutando bitonic_sort secuencial..." << endl;

    if (n <= 0)
        return;

    // Si ya es potencia de 2, ordenar directamente
    if ((n & (n - 1)) == 0)
    {
        bitonicSort(v, 0, n, true); //Si el algoritmo ya es potencia de 2, se ordena directamente
        checkSorted(v, n);
        return;
    }

    // Obtener la siguiente potencia de 2
    size_t newSize = static_cast<size_t>(nextPowerOfTwo(n));

    // Crear un vector temporal con el nuevo tamaño (evita problemas de sobre escritura)
    std::vector<int> temp;
    temp.resize(newSize);

    // Copiar los datos originales
    for (size_t i = 0; i < static_cast<size_t>(n); ++i)
        temp[i] = v[i];

    // Rellenar con el valor máximo posible
    for (size_t i = static_cast<size_t>(n); i < newSize; ++i)
        temp[i] = numeric_limits<int>::max();

    // Ordenar el arreglo temporal
    bitonicSort(temp.data(), 0, static_cast<int>(newSize), true);

    // Copiar únicamente los datos originales ya ordenados
    for (int i = 0; i < n; ++i)
        v[i] = temp[i];
	checkSorted(v, n);
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