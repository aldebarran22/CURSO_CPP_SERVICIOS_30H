// memoria.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

void conPunteros() {
    int** ptr = nullptr;

    // Reservar 1) para 10 filas:
    ptr = new int* [10];
    for (int i = 0; i < 10; i++) {
        // Reservar para 10 cols en cada fila
        ptr[i] = new int[10];
       
    }

    // Se libera al revés:
    for (int i = 0; i < 10; i++) {
        // Liberar cada fila de 10 cols
        delete[] ptr[i];
    }
    // Liberar los punteros de las filas:
    delete[] ptr;
}

void conSmartPointers() {
    std::unique_ptr<std::unique_ptr<int[]>[]> ptr = std::make_unique<std::unique_ptr<int[]>[]>(10);
    // Equivale a: ptr = new int* [10];

    // Crear cada una de las filas:
    for (int i = 0; i < 10; i++) {
        ptr[i] = std::make_unique<int[]>(10);
        // Equivale a:  ptr[i] = new int[10];
    }

    // NO hay que liberar, se libera automáticamente
}


int main()
{
    //conPunteros();
    conSmartPointers();
}

