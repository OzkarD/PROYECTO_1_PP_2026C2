/*
    PAREJA 2
    - Yael Jimena Chale Pech    -   11245
    - Luigi Velazquez Vega      -   11413

    SEQUENTIAL SELECTION SORT (SSS)

    El algoritmo ordena un arreglo buscando el elemento más pequeño
    de la parte no ordenada e intercambianadolo en su posición correcta.
    El algoritmo consta de dos bucles anidados donde el primer for recorre
    cada posición i del arreglo, se asume que inicialmente que su valor es el
    mínimo, mientras que, en el segundo for se comparan los elementos restantes
    para encontrar el verdadero mínimo, al finalizar el segundo for se 
    intercambia la posición en la que se encuentra el primer for con el valor mínimo.

    PARALLEL QUICK SORT (PQS)
    
    El algoritmo ordena un arreglo utilizando un pivote para dividirlo
    en dos partes. Primero, la función partition coloca los elementos menores
    o iguales al pivote del lado izquierdo y los mayores del lado derecho, dejando
    al pivote en su posición correcta.

    Después de obtener la posición del pivote, se utiliza #pragma omp parallel
    for para repartir las dos partes del arreglo entre los hilos. Un hilo ordena
    de forma recursiva la parte izquierda y otro hilo ordena la parte derecha.
    Como ambas partes se encuentran en posiciones diferentes del arreglo, pueden
    procesarse al mismo tiempo.

    Cada parte utiliza la función recursiva de Quick Sort hasta que las divisiones
    tienen uno o ningún elemento, dejando el arreglo ordenado.

 */


#include "selection_sort.h"
#include "quick_sort.h"
#include "vector_tools.h"
#include <iostream>
#include <omp.h>

using namespace std;

// Función swap se implementa en el selection y el quick sort
static void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Función del QUICK sort
// Función auxiliar para particionar el arreglo
static int partition(int* v, int low, int high)
{
    int pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (v[j] <= pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[high]);

    return i + 1;
}

// Función del QUICK sort
// Función recursiva de Quick Sort
static void quickSortRecursive(int* v, int low, int high)
{
    if (low < high)
    {
        int pi = partition(v, low, high);

        quickSortRecursive(v, low, pi - 1);
        quickSortRecursive(v, pi + 1, high);
    }
}

//FUNCIÓN PRINCIPAL DEL SELECTION SORT
void sequential::selection_sort(int* v, int n)
{

    for (int i = 0; i < n - 1; i++)
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

//FUNCIÓN PRINCIPAL DEL QUICK SORT
void parallel::quick_sort(int* v, int n)
{
    if (v == nullptr || n <= 1)
        return;

    int pi = partition(v, 0, n - 1);

#pragma omp parallel for shared(v)
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            // Primer hilo
            quickSortRecursive(v, 0, pi - 1);
        }
        else
        {
            // Segundo hilo
            quickSortRecursive(v, pi + 1, n - 1);
        }
    }
    checkSorted(v, n);
}


//MAIN DE PRUEBA
int main()
{
    srand((unsigned)time(NULL));
    UserData data = getUserData();

    const int N = 1 << data.bit_shift;
    int* vector = createVector(N);
    fillRandom(vector, N, data.min_value, data.max_value);
    printSample(vector, N, 10);

    int* vector_copy = createVector(N);

    cout << "Ejecutando Sequential selection_sort" << endl;
    double omp_begin_sel = omp_get_wtime();
    copyVector(vector, vector_copy, N);
    sequential::selection_sort(vector_copy, N);
    double omp_end_sel = omp_get_wtime();

    cout << "Ejecutando Parallel Quick_sort" << endl;
    double omp_begin_quick = omp_get_wtime();
    copyVector(vector, vector_copy, N);
    parallel::quick_sort(vector_copy, N);
    double omp_end_quick = omp_get_wtime();

    cout << "\n" << "***** TIEMPO DE EJECUCION *****" << "\n" << endl;
    cout << "Tiempo omp del sequential selection sort " << (omp_end_sel - omp_begin_sel) << endl;
    cout << "Tiempo omp del parallel quick sort " << (omp_end_quick - omp_begin_quick) << endl;


    destroyVector(vector);
    destroyVector(vector_copy);
    return 0;
}


