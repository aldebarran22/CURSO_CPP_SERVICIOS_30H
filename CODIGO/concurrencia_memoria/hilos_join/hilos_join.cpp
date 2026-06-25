// hilos_join.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

void generarAleatorios(int n, int limite, int mili, int& suma) {

    for (int i = 0; i < n; i++) {
        int num = std::rand() % limite;
        std::cout << "Aleatorio: " << i << ": " << num << std::endl;
        suma += num;

        std::this_thread::sleep_for(std::chrono::milliseconds(mili));
    }
}

int main()
{
    int suma = 0;

    // Crear un hilo a partir de una función, pasando parámetros por copia y por referencia:
    std::thread hiloFuncion{ generarAleatorios, 10, 250, 500, std::ref(suma) };
    hiloFuncion.join();

    std::cout << "La suma de aleatorios es:  " << suma << std::endl;

    return 0;
}

