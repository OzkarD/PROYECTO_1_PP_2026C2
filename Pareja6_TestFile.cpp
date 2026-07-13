#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include "bitonic_sort.h"
#include <iomanip>
#include "omp.h"

using namespace std;

int num_threads = omp_get_max_threads();

double p = static_cast<double>(num_threads);

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

double log2(double n)
{
    return log(n) / log(2.0);
}

void printMetricRow(const char *name, double T1, double Tinf)
{
    double parallelism;
    int Pmin;

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

    cout << setw(35) << left << name << " | " << setw(15) << T1 << " | " << setw(15) << Tinf << " | " << setw(18) << parallelism << " | "  << setw(13) << Pmin << " | "  << setw(15) << endl;
}

void printTheoreticalMetrics(int size)
{
    int n = size;

    double dn = static_cast<double>(n);

    double logn = log2(dn);

    double T1;
    double Tinf;

    cout << endl <<"Metricas teoricas para n = " << n << endl;

    cout << setw(37) << left << "Algoritmo" << setw(18) << "T1" << setw(19) << "Tinf" << setw(20) << "Paralelismo" << setw(20) << "Pmin" << endl;
    cout << string(110, '-') << endl;

    /*
        ALGORITMOS SECUENCIALES
        En los algoritmos secuenciales:
        Tinf = T1
        Paralelismo = 1
        Pmin = 1
    */

    // Sequential Bubble Sort - O(n^2)
    T1 = dn * dn;
    Tinf = T1;
    printMetricRow("Sequential Bubble-Sort", T1, Tinf);

    // Sequential Selection Sort - O(n^2)
    T1 = dn * dn;
    Tinf = T1;
    printMetricRow("Sequential Selection-Sort", T1, Tinf);

    // Sequential Insertion Sort - O(n^2)
    T1 = dn * dn;
    Tinf = T1;
    printMetricRow("Sequential Insertion-Sort", T1, Tinf);

    // Sequential Merge Sort - O(n log n)
    T1 = dn * logn;
    Tinf = T1;
    printMetricRow("Sequential Merge-Sort", T1, Tinf);

    // Sequential Quick Sort - O(n log n), caso promedio
    T1 = dn * logn;
    Tinf = T1;
    printMetricRow("Sequential Quick-Sort", T1, Tinf);

    // Sequential Bitonic Sort - O(n log^2 n)
    T1 = dn * logn * logn;
    Tinf = T1;
    printMetricRow("Sequential Bitonic-Sort", T1, Tinf);

    /*
        ALGORITMOS PARALELOS
    */

    // Parallel Bubble Sort - Odd-Even Sort
    // T1 = O(n^2), Tinf = O(n)
    T1 = (dn * dn) / 2.0;
    Tinf = dn;
    printMetricRow("Parallel Bubble-Sort", T1, Tinf);

    // Parallel Selection Sort
    // T1 = O(n^2), Tinf = O(n log n)
    if (p < 1.0)
        p = 1.0;

    double selectionComparisons = (dn * (dn - 1.0)) / 2.0;

    double sequentialReductions = p * (dn - 1.0);

    T1 = selectionComparisons + sequentialReductions;

    Tinf = (selectionComparisons / p) + sequentialReductions;
    printMetricRow("Parallel Selection-Sort", T1, Tinf);

    // Parallel Insertion Sort
    // T1 = O(n^2), Tinf = O(n log n)
    T1 = (dn * dn) / 2.0;
    Tinf = dn;
    printMetricRow("Parallel Insertion-Sort", T1, Tinf);

    // Parallel Merge Sort
    // T1 = O(n log n), Tinf = O(log^3 n)
    T1 = dn * logn;
    Tinf = logn * logn * logn;
    printMetricRow("Parallel Merge-Sort", T1, Tinf);

    // Parallel Quick Sort
    // T1 = O(n log n), Tinf = O(log^2 n), caso promedio
    T1 = dn * logn;

    Tinf = dn + (dn / 2.0) * (logn - 1.0);
    printMetricRow("Parallel Quick-Sort", T1, Tinf);

    // Parallel Bitonic Sort
    // T1 = O(n log^2 n), Tinf = O(log^2 n) 
    double bitonicStages = (logn * (logn + 1.0)) / 2.0;

    T1 = (dn / 2.0) * bitonicStages;

    Tinf = bitonicStages;
    printMetricRow("Parallel Bitonic-Sort", T1, Tinf);
}

void printAssignmentReminder(void)
{
    cout << "\nRecordatorio: incluir TDG, T1, Tinf, paralelismo=T1/Tinf y Pmin.\n" << endl;
    return;
}


int main(){
    int n = 1<<20; // Tamaño del vector (2^20)
    cout << "hilos disponibles para paralelismo: "<< p << endl;
    printTheoreticalMetrics(n);
    printAssignmentReminder();
    return 0;
}