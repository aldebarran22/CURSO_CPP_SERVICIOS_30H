// hilos_join.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>

void generarAleatorios(int n, int limite, int mili, int& suma) {

    for (int i = 0; i < n; i++) {
        int num = std::rand() % limite;
        std::cout << "Aleatorio: " << i << ": " << num << std::endl;
        suma += num;

        std::this_thread::sleep_for(std::chrono::milliseconds(mili));
    }
}

class Hilo {
    int id;
    int n;
    int tiempo;

public:
    Hilo(int id, int n=5, int tiempo=1):id(id), n(n), tiempo(tiempo){}

    void operator()() {
        for (int i = 0; i < n; i++) {
            std::cout << "Operador("<< id << ")" << " " << i << ": " << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(tiempo));
        }
    }
};

class hilo2 : public std::thread {

};

int main()
{
    int suma = 0;
    int nMensajes = 6;
    int ml = 350;
    
    // Crear un hilo a partir de una función, pasando parámetros por copia y por referencia:
    /*
    std::thread hiloFuncion{ generarAleatorios, 10, 250, 500, std::ref(suma) };
    

    std::thread hiloLambda([nMensajes, ml]() {
        for (int i = 0; i < nMensajes; i++) {
            std::cout << "mensaje lambda: " << (i + 1) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(ml));
        }
    });*/

    std::vector<std::thread> hilos;

    for (int i = 0; i < 3; i++) {
        Hilo hilo(i, i + 5);
        std::thread hiloObjeto(hilo);
        hilos.emplace_back(hiloObjeto);
    }

    for (auto& h : hilos) {
        h.join();
    }


    // Esperar a que terminen los hilos
    //hiloFuncion.join();
    //hiloLambda.join();
    //hiloObjeto.join();

    //std::cout << "La suma de aleatorios es:  " << suma << std::endl;

    return 0;
}

