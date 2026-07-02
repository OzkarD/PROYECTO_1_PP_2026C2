/*
Pareja 5 - Ari Martinez / Arturo Pelcastre

Algoritmo asignado en esta etapa:
Sequential Quick Sort (SQS)

Trabajo realizado:
Se implemento el algoritmo Quick Sort secuencial en el archivo quick_sort.cpp,
respetando la firma definida en quick_sort.h:

namespace sequential
{
    void quick_sort(int* v, int n);
}

La implementacion utiliza una funcion auxiliar de particion, una funcion
recursiva y una funcion auxiliar para intercambiar valores.

Conclusion:
Durante este avance se implemento el algoritmo Quick Sort secuencial respetando
las firmas, archivos y namespaces definidos por los integradores.
El algoritmo ordena el vector dividiendolo mediante un pivote y aplicando
recursion sobre las partes izquierda y derecha.
Se incluyo este archivo de prueba deshabilitado para evitar conflictos con
el main principal del proyecto.
La validacion completa desde main queda pendiente hasta que el benchmark este
implementado por la pareja asignada.
*/

#if 0

#include <iostream>
#include "quick_sort.h"

using namespace std;

static void printVector(const int* v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }

    cout << endl;
}

static bool isSorted(const int* v, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (v[i - 1] > v[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int v1[] = { 9, 3, 8, 5, 1, 6, 3, 7, 3, 1 };
    int n1 = sizeof(v1) / sizeof(v1[0]);

    cout << "Prueba 1 - Vector original:" << endl;
    printVector(v1, n1);

    sequential::quick_sort(v1, n1);

    cout << "Prueba 1 - Vector ordenado:" << endl;
    printVector(v1, n1);

    cout << "Validacion: "
        << (isSorted(v1, n1) ? "Ordenado correctamente" : "Error")
        << endl;

    int v2[] = { 5, -3, 0, 5, -10, 8, 1 };
    int n2 = sizeof(v2) / sizeof(v2[0]);

    cout << "\nPrueba 2 - Vector con negativos:" << endl;
    printVector(v2, n2);

    sequential::quick_sort(v2, n2);

    cout << "Prueba 2 - Vector ordenado:" << endl;
    printVector(v2, n2);

    cout << "Validacion: "
        << (isSorted(v2, n2) ? "Ordenado correctamente" : "Error")
        << endl;

    return 0;
}

#endif