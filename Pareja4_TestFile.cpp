#include "merge_sort.h"
#include <iostream>


#include <stdlib.h> //Implementado por integrador
#include <time.h>//Implementado por integrador

using namespace std;

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

void sequential::merge_sort(int* v, int n)
{
    cout << "Ejecutando merge_sort secuencial..." << endl;

    if (n <= 1)
        return;

    mergeSort(v, 0, n - 1);
}

/*
void parallel::merge_sort(int* v, int n)
{
    cout << "Ejecutando merge_sort paralelo..." << endl;
    return;
}
*/

//---------------------------------------------------------------------------------

//Implementado por integrador
int main(void)
{
    int array1[] = {-4, 2, -6, 8, 1, -3, 5, -7, 0, -9};
    int size = 10;

        for(int i = 0; i < 10;i++)
        {
            printf("%d ",array1[i]);
        }
        printf("\n");

       sequential::merge_sort(array1,size);

       for(int i = 0; i < 10;i++)
        {
            printf("%d ",array1[i]);
        }
        printf("\n");
    //----------------------------------------------

        printf("Parte dos a continuacion...\n");

        int size2 = 1e8;
        int* array2 = new int[size2];

        srand(time(NULL));

        for(int i = 0; i < size2; i++)
        {
            array2[i] = rand();

            if(i < 10)
            {
                printf("%d ",array2[i]);
            }
        }
        printf("\n");

        sequential::merge_sort(array2,size2);

        for(int j = 0; j < 10; j++)
        {
            printf("%d ",array2[j]);
        }
        printf("\n");

        printf("Se imprimio.\n");


         delete[] array2;

        return 0;
}