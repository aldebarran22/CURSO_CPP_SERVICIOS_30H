// hilos_join.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <ctime>

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
    std::mutex& m;

public:
    Hilo(int id, std::mutex& m, int n=5, int tiempo=1):id(id), m(m), n(n), tiempo(tiempo) {}

    void operator()() {
        {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "Inicia el Operador(" << id << ")" << std::endl;
        }

        for (int i = 0; i < n; i++) {
            {
                std::lock_guard<std::mutex> lock(m);
                std::cout << "Operador(" << id << ")" << " " << i << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(tiempo));
        }

        {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "Termina el Operador(" << id << ")" << std::endl;
        }
    }
};

class hilo2 : public std::thread {

};

int main()
{
    std::srand(std::time(nullptr));
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

    std::mutex m;
    std::vector<std::thread> hilos;

    for (int i = 0; i < 3; i++) {        
        std::thread hiloObjeto(Hilo(i, std::ref(m), 1+std::rand()%10, std::rand()%3));
        hilos.push_back(std::move(hiloObjeto));        
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

