/*
PAREJA A CRAGO: Pareja 7 - Gerardo Martínez / Pedro Meza

En este archivo se ha de desarrollar la lógica del benchmark.h y se ha de 
documentar el código de tal forma que como mínimo, se expliquen el funcionamiento de variables, de funciones
y de librerias extra que sean usadas.  

NOTA: Revisar el benchmark.cpp de prácticas pasadas. En general, se incluyen funciones de 
	OMP y Chrono.
*/
#include <iostream>
#include <chrono>
#include <iomanip>
#include <omp.h>
#include "benchmark.h"

ResultTime benchmarkSortingMethod(Sorting_Method Method, const int* v, int size, int repetitions)
{
	ResultTime Tiempo;

	Tiempo.omp_time = 1e100;
	Tiempo.chrono_time = 1e100;
    for (int r = 0; r < repetitions; r++)
    {
        auto chrono_begin = std::chrono::high_resolution_clock::now();
        double omp_begin = omp_get_wtime();

        // Ejecuta el algoritmo recibido.
        Method(const_cast<int*>(v), size);

        double omp_end = omp_get_wtime();
        auto chrono_end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = chrono_end - chrono_begin;

        // Conserva únicamente el mejor tiempo.
        if (elapsed.count() < Tiempo.chrono_time)
        {
            Tiempo.chrono_time = elapsed.count();
            Tiempo.omp_time = omp_end - omp_begin;
        }
    }
	return Tiempo;
}

static void printRow(const char* method,
    const ResultTime& result,
    double sequential_time)
{
    double speedup = sequential_time / result.chrono_time;

    std::cout
        << std::left
        << std::setw(28) << method
        << std::setw(18) << result.chrono_time
        << std::setw(18) << result.omp_time
        << std::setw(12) << speedup
        << std::endl;
}

void printBenchmarkTable(ResultTime& seq_bitonic, ResultTime& par_bitonic,
						ResultTime& seq_bubble, ResultTime& par_bubble,
						ResultTime& seq_insertion, ResultTime& par_insertion,
						ResultTime& seq_merge, ResultTime& par_merge,
						ResultTime& seq_quick, ResultTime& par_quick,
						ResultTime& seq_selection, ResultTime& par_selection)
{
    std::cout << "\n\n";
    std::cout << std::left
        << std::setw(28) << "Metodo"
        << std::setw(18) << "Chrono (s)"
        << std::setw(18) << "OMP (s)"
        << std::setw(12) << "Speedup"
        << std::endl;

    std::cout << "-------------------------------------------------------------------------------"
        << std::endl;

    printRow("Bitonic Secuencial", seq_bitonic, seq_bitonic.chrono_time);
    printRow("Bitonic Paralelo", par_bitonic, seq_bitonic.chrono_time);

    printRow("Bubble Secuencial", seq_bubble, seq_bubble.chrono_time);
    printRow("Bubble Paralelo", par_bubble, seq_bubble.chrono_time);

    printRow("Insertion Secuencial", seq_insertion, seq_insertion.chrono_time);
    printRow("Insertion Paralelo", par_insertion, seq_insertion.chrono_time);

    printRow("Merge Secuencial", seq_merge, seq_merge.chrono_time);
    printRow("Merge Paralelo", par_merge, seq_merge.chrono_time);

    printRow("Quick Secuencial", seq_quick, seq_quick.chrono_time);
    printRow("Quick Paralelo", par_quick, seq_quick.chrono_time);

    printRow("Selection Secuencial", seq_selection, seq_selection.chrono_time);
    printRow("Selection Paralelo", par_selection, seq_selection.chrono_time);
	return;
}
