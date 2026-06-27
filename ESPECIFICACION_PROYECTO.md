# Proyecto — Algoritmo de ordenamiento

## Objetivo
Implementar y analizar algoritmos secuenciales y paralelos en C++ con OpenMP.

## Namespaces
- `sequential`: algoritmos secuenciales.
- `parallel`: algoritmos paralelos.

## Archivos
Todos los archivos están separados por archivos y en cada archivo se encuentra la versión secuencial y la 
versión paralela.
- `bubble_sort.cpp`
- `selection_sort.cpp`
- `insertion_sort.cpp`
- `merge_sort.cpp`
- `quick_sort.cpp`
- `bitonic_sort.cpp`

## Requisitos
- El usuario define tamaño, repeticiones y rango del vector. El rango acepta negativos.
- El programa reporta `std::chrono`, `omp_get_wtime`, speedup y validación de ordenamiento.
- Todos los algoritmos deben ser implementados en C++ y OpenMP, y deben ser probados con vectores de tamaño 10^6 a 10^8.
- Todos los developers deben crear su archivo de prueba y dejarlo deshabilitado en el commit final.
- En el último commit, deberán aparecer todos los archivos de prueba deshabilitados y el archivo `main.cpp` habilitado.
- Indentificar el archivo de prueba como: ParejaX_TestFile.cpp
- En caso de que los integradores rechacen una implementación, deberan poner un comentario en git:
			ejemplo: cambio rechazado-se rompe el build, favor de revisar.	
- No se deben alterar las firmas de las funciones, ni los nombres de los archivos, ni los namespaces.
- Si se me paso algo, favor de avisarme para agregarlo a la especificación. :)
- Redactar una conclusión del trabajo realizado con un mínimo en 4 líneas en el archivo de prueba.

## Sugerencia

-- Pueden seguir esta secuencia de pasos para implementar su proyecto:

## While(1)
## {
	Despertar();
	Tomar café();
	Programar();
	Comer();
	Tomar café();
	Programar();
	if(tengo vida social... ja)
	{
		break();
	}
	else
	{
       Dormir();
	}
	Dormir();
## }





