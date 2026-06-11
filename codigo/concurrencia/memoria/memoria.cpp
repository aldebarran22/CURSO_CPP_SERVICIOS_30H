// memoria.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

int main()
{
	int** ptr = nullptr;

	ptr = new int* [10];
	for (int i = 0; i < 10; i++) {
		ptr[i] = new int[10];

	}

	delete[] ptr;
}
