// punteros.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <memory>
#include "Vector.h"

void testC() {
    int n = 10;
    int* ptr= nullptr;
    int* ptr2 = nullptr;

    ptr = (int*)std::malloc(sizeof(int) * n); // Bloque completo en bytes
    ptr2 = (int*)std::calloc(n, sizeof(int)); // numero de elementos * ocupan, inicializa a cero los elementos

    // Realloc, ampliar un bloque de memoria:
    // Ampliar m elementos:
    int m = 5;

    ptr = (int*)std::realloc(ptr, (static_cast<unsigned long long>(n) + m) * sizeof(int)); // puntero original y tamaño total final.

    free(ptr);
    free(ptr2);
}

void testVector() {
    Vector v1, v3;

    v1.add(8);
    v1.add(18);
    v1.add(28);
    v1.add(38);

    std::cout << "v1" << std::endl;
    v1.imprimir();

    // Constructor copia:
    Vector v2(v1);

    v1.add(99);

    std::cout << "v1" << std::endl;
    v1.imprimir();

    std::cout << "v2" << std::endl;
    v2.imprimir();

    // Operador igual:
    v3 = v1;

    std::cout << "v3" << std::endl;
    v3.imprimir();
}


void testSP() {
    auto a_ptr = std::unique_ptr<int>(new int);
    //auto b_ptr = a_ptr; No te deja hacer la copia!
}

int main()
{
    //testVector();
    testSP();
    return 0;
}

