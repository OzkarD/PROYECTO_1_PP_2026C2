#include <cstring>
#include <iostream>
#include <cstdlib>
#include "vector_tools.h"
#include "config.h"

int* createVector(int n)
{
    if(n <= 0) return nullptr;
    return new int[n];
}

void destroyVector(int* v)
{
    delete[] v;
}

void fillRandom(int* v, int n, int min_value, int max_value)
{
	for(int i = 0; i < n;i++)
	{
		v[i] = min_value + rand() % (max_value - min_value + 1);
	}
}

void printSample(const int* v, int n, int max_items)
{
	if(n <= 0||v == nullptr) return;
	if(max_items > n) max_items = n;
	for(int i = 0;i < max_items;i++)
	{
		std::cout<<v[i]<<" ";
	}
	std::cout<<std::endl;
}

void checkSorted(const int* v, int n)
{
	if(n <= 0||v == nullptr) return;
	for(int i = 0;i < n - 1;i++)
	{
		if (v[i] > v[i + 1])
		{
			std::cout<<"El arreglo no esta ordenado."<<std::endl;
			return;
		}
	}
	std::cout<<"El arreglo esta ordenado."<<std::endl;
}

UserData getUserData()
{
	UserData data;
	std::cout<<"Ingrese el valor de bits que desea recorrer (1<<N): ";
	std::cin>>data.bit_shift;
	while(data.bit_shift < 1||data.bit_shift > 30)
	{
		std::cout<<"El valor de bits debe estar entre 1 y 30. Ingrese nuevamente: ";
		std::cin>>data.bit_shift;
		std::cout<<std::endl;
	}
	std::cout<<"Ingrese el valor minimo del rango de numeros (pueden ser negativos): ";
	std::cin>>data.min_value;
	std::cout<<"Ingrese el valor maximo del rango de numeros: ";
	std::cin>>data.max_value;
	if(data.max_value < data.min_value)
	{
		std::cout<<"El valor maximo no puede ser menor que el valor minimo. Intercambiando valores."<<std::endl;
		std::swap(data.min_value, data.max_value);
	}
	std::cout<<"Ingrese el numero de repeticiones: ";
	std::cin>>data.repetitions;
	while(data.repetitions < 1)
	{
		std::cout<<"El numero de repeticiones debe ser al menos 1. Ingresa nuevamente: ";
		std::cin>>data.repetitions;
		std::cout<<std::endl;
	}
	return data;
}

void copyVector(const int* source, int* destination, int n)
{
	std::memcpy(destination, source, n * sizeof(int));
}