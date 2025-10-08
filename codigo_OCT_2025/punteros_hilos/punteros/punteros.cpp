// punteros.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Vector.h"

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


int main()
{
    testVector();
    return 0;
}

