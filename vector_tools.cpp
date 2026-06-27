#include "vector_tools.h"

int* createVector(int n)
{
    if(n <= 0)
	{
        return nullptr;
    }
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
	if(n <= 0||v == nullptr)
	{
		return;
	}
	for(int i = 0;i < max_items;i++)
	{
		std::cout<<v[i]<<" ";
	}
	std::cout<<std::endl;
}

void checkSorted(const int* v, int n)
{
	if(n <= 0||v == nullptr)
	{
		return;
	}
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