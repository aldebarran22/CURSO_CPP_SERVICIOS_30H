// memoria.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <memory>
#include <vector>

void conPunteros()
{
	int** ptr = nullptr;

	// 1) Puntero exterior
	ptr = new int* [10];

	// 2) Punteros interiores:
	for (int i = 0; i < 10; i++) {
		ptr[i] = new int[10];
	}
	
	// 1) liberar punteros interiores
	for (int i = 0; i < 10; i++) {
		delete[] ptr[i];
	}

	// 2) liberar puntero exterior
	delete[] ptr;

}

void conSmartPointers()
{
	// ptr = new int* [10];
	std::unique_ptr<std::unique_ptr<int[]>[]> ptr = std::make_unique<std::unique_ptr<int[]>[]>(10);

	
	// Crear la filas:
	for (int i = 0; i < 10; i++) {
		// ptr[i] = new int[10];
		ptr[i] = std::make_unique<int[]>(10);

	}
}

void conVector()
{
	std::vector<std::vector<int>> matriz(10, std::vector<int>(10));

	matriz[3][4] = 0;
	matriz.at(3).at(5) = 0;
}

int main()
{
	// Reservar para una matriz:
	//conPunteros();
	conSmartPointers();
	//conVector();
}

