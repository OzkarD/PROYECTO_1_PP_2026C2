#include "bubble_sort.h"
#include <iostream>

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
    return;
}

void parallel::bubble_sort(int* v, int n) 
{
    cout << "Ejecutando bubble_sort paralelo..." << endl;
    return;
}