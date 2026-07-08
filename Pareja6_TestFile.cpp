#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include "bitonic_sort.h"
#include <iomanip>

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

    
}


double log2_custom(double n)
{
    return log(n) / log(2.0);
}

void printMetricRow(const char *name, double T1, double Tinf)
{
    double parallelism;
    double Pmin;

    if (Tinf == 0)
    {
        parallelism = 0;
        Pmin = 0;
    }
    else
    {
        parallelism = T1 / Tinf;
        Pmin = ceil(parallelism);
    }

    cout << name << " | " << T1 << " | " << Tinf << " | " << parallelism << " | " << Pmin << endl;
}

void printTheoreticalMetrics(int size)
{
    int n = size;

    double logn = log2_custom(n);

    double T1;
    double Tinf;

    cout << endl <<"Metricas teoricas para n = " << n << endl;

    cout << setw(35) << left << "Algoritmo" << setw(12) << "T1" << setw(12) << "Tinf" << setw(12) << "Paralelismo" << setw(12) << "Pmin" << endl;
    cout << string(80, '-') << endl;

    /*
        ALGORITMOS SECUENCIALES
        En los algoritmos secuenciales:
        Tinf = T1
        Paralelismo = 1
        Pmin = 1
    */

    // Sequential Bubble Sort - O(n^2)
    T1 = n;
    Tinf = n * n;
    printMetricRow("Sequential Bubble-Sort", T1, Tinf);

    // Sequential Selection Sort - O(n^2)
    T1 = n;
    Tinf = n * n;
    printMetricRow("Sequential Selection-Sort", T1, Tinf);

    // Sequential Insertion Sort - O(n^2)
    T1 = n;
    Tinf = n * n;
    printMetricRow("Sequential Insertion-Sort", T1, Tinf);

    // Sequential Merge Sort - O(n log n)
    T1 = n;
    Tinf = n * logn;
    printMetricRow("Sequential Merge-Sort", T1, Tinf);

    // Sequential Quick Sort - O(n log n), caso promedio
    T1 = n;
    Tinf = n * logn;
    printMetricRow("Sequential Quick-Sort", T1, Tinf);

    // Sequential Bitonic Sort - O(n log^2 n)
    T1 = n;
    Tinf = n * logn * logn;
    printMetricRow("Sequential Bitonic-Sort", T1, Tinf);

    /*
        ALGORITMOS PARALELOS
    */

    // Parallel Bubble Sort - Odd-Even Sort
    // T1 = O(n^2), Tinf = O(n)
    T1 = n * n;
    Tinf = n;
    printMetricRow("Parallel Bubble-Sort", T1, Tinf);

    // Parallel Selection Sort
    // T1 = O(n^2), Tinf = O(n log n)
    T1 = n * n;
    Tinf = n * logn;
    printMetricRow("Parallel Selection-Sort", T1, Tinf);

    // Parallel Insertion Sort
    // T1 = O(n^2), Tinf = O(n log n)
    T1 = n * n;
    Tinf = n * logn;
    printMetricRow("Parallel Insertion-Sort", T1, Tinf);

    // Parallel Merge Sort
    // T1 = O(n log n), Tinf = O(log^3 n)
    T1 = n * logn;
    Tinf = logn * logn * logn;
    printMetricRow("Parallel Merge-Sort", T1, Tinf);

    // Parallel Quick Sort
    // T1 = O(n log n), Tinf = O(log^2 n), caso promedio
    T1 = n * logn;
    Tinf = logn * logn;
    printMetricRow("Parallel Quick-Sort", T1, Tinf);

    // Parallel Bitonic Sort
    // T1 = O(n log^2 n), Tinf = O(log^2 n)
    T1 = n * logn * logn;
    Tinf = logn * logn;
    printMetricRow("Parallel Bitonic-Sort", T1, Tinf);
}

void printAssignmentReminder(void)
{
    cout << "\nRecordatorio: incluir TDG, T1, Tinf, paralelismo=T1/Tinf y Pmin.\n" << endl;
    return;
}


