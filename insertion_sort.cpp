#include "insertion_sort.h"
#include <iostream>
#include <omp.h>
#include "vector_tools.h"

using namespace std;

void sequential::insertion_sort(int* v, int n) 
{
    cout << "Ejecutando insertion_sort secuencial..." << endl;
    for (int i = 1; i < n; i++)
    {
        int key = v[i];
        int j = i - 1;

		while (j >= 0 && v[j] > key)
		{
			v[j + 1] = v[j];
			j--;
		}

        v[j + 1] = key;
        
    }
	checkSorted(v, n);
    return;
}

void parallel::insertion_sort(int* v, int n)
{
    cout << "Ejecutando insertion_sort paralelo..." << endl;
    if (v == nullptr || n <= 1)
        return;

    for (int phase = 0; phase < n; phase++)
    {
        if (phase % 2 == 0)
        {
#pragma omp parallel for
            for (int i = 1; i < n; i += 2)
            {
                if (v[i - 1] > v[i])
                {
                    int temp = v[i];
                    v[i] = v[i - 1];
                    v[i - 1] = temp;
                }
            }
        }
        else
        {
#pragma omp parallel for
            for (int i = 1; i < n - 1; i += 2)
            {
                if (v[i] > v[i + 1])
                {
                    int temp = v[i];
                    v[i] = v[i + 1];
                    v[i + 1] = temp;
                }
            }
        }
    }
	checkSorted(v, n);
}