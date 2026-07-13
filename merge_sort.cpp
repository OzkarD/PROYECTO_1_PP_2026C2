#include "merge_sort.h"
#include <iostream>
#include "vector_tools.h"
#include <omp.h>

using namespace std;
//----------------------------------------------------------------------------------------------------------

void merge(int* v, int left, int mid, int right) // Función auxiliar para fusionar dos arreglos ya ordenados
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = v[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = v[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}
//----------------------------------------------------------------------------------------------------------

void mergeSort(int* v, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(v, left, mid);
        mergeSort(v, mid + 1, right);
        merge(v, left, mid, right);
    }
}
//----------------------------------------------------------------------------------------------------------

void merge_sort_parallel(int* v, int left, int right)
{
    // cout << "Ejecutando merge_sort paralelo..." << endl;

    if (left >= right)
    {
        return;
    }


    int mid = left + (right - left) / 2;

    #pragma omp task
    merge_sort_parallel(v, left, mid);

    #pragma omp task
    merge_sort_parallel(v, mid + 1, right);

    #pragma omp taskwait
    merge(v, left, mid, right);

}
//----------------------------------------------------------------------------------------------------------

void sequential::merge_sort(int* v, int n)
{
    cout << "Ejecutando merge_sort secuencial..." << endl;

    if (n <= 1)
        return;

    mergeSort(v, 0, n - 1);
	checkSorted(v, n);
}

void parallel::merge_sort(int* v, int n)
{
    cout << "Ejecutando merge_sort paralelo..." << endl;
    if (n <= 1)
        return;

    merge_sort_parallel(v, 0, n - 1);
	checkSorted(v, n);
}