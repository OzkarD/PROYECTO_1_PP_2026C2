#include "selection_sort.h"
#include "vector_tools.h"
#include <iostream>

using namespace std;

void sequential::selection_sort(int* v, int n)
{
    cout << "Ejecutando selection sort en secuencial...\n" << endl;

    for (int i = 0; i < n-1; i++)
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
    return;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}