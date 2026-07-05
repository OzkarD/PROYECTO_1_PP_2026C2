#include "insertion_sort.h"
#include <iostream>

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
    return;
}

void parallel::insertion_sort(int* v, int n) 
{
    cout << "Ejecutando insertion_sort paralelo..." << endl;
    return;
}