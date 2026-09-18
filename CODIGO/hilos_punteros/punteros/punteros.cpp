// punteros.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

void testPunteros()
{
    int** ptr = nullptr;

    ptr = new int* [10];

    for (int i = 0; i < 10; i++) {
        ptr[i] = new int[10];
    }

    // Se libera la memoria al reves:
    for (int i = 0; i < 10; i++) {
        delete[] ptr[i];
    }

    delete[] ptr;
}

void testSmartPointers()
{

}


int main()
{
    testPunteros();
    testSmartPointers();
}

