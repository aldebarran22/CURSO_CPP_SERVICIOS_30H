// punteros.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <memory>
#include <vector>

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
    std::unique_ptr<std::unique_ptr<int[]>[]> ptr = std::make_unique<std::unique_ptr<int[]>[]>(10);

    //auto ptr2 = std::move(ptr); Mover si se permite!

    // Crear las filas:
    for (int i = 0; i < 10; i++) {
        ptr[i] = std::make_unique<int[]>(10);
    }
}

void testVector()
{
    std::vector<std::vector<int>> matriz(10, std::vector<int>(10));

    matriz[3][4] = 0;
    matriz.at(3).at(5) = 0;
}

struct A {
    A(int a) {
        std::cout << "Se crea el objeto…\n"; }
            
    ~A() {
            std::cout << "Se elimina el objeto…\n"; }
};

int main()
{
    //testPunteros();
    //testSmartPointers();
    //testVector();

    // Equivalente a: std:: shared_ptr<A>(new A(10));
    auto a_ptr = std::make_shared<A >(10);

    std::cout << a_ptr.use_count() << std::endl;
    {
        auto b_ptr = a_ptr;
        std::cout << a_ptr.use_count() << std::endl;
    }
    std::cout << "En el scope de main\n";
    std::cout << a_ptr.use_count() << std::endl;
    return 0;
}

