#include "bubble_sort.h"
//#include "bubble_sort.cpp"
#include <iostream>

#include <stdlib.h> //Implementado por integrador
#include <time.h>//Implementado por integrador
#include <time.h>


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

/*
void parallel::bubble_sort(int* v, int n) 
{
    cout << "Ejecutando bubble_sort paralelo..." << endl;
    return;
}
*/

//Implementado por el integrador
/*
int main(void)
{
    srand(time(NULL));

    int size = 100000;
    //int array[1e8] = {0};

    int* array = new int[size];

    for(int i = 0; i < 20; i++)
    {
        array[i] = rand();
        printf("%d ", array[i]);
    }
    printf("\n");

    sequential::bubble_sort(array, size);

    for(int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
*/