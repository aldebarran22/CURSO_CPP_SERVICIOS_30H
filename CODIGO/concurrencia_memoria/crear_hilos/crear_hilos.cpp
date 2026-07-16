// crear_hilos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>


void generarAleatorios(int n, int limite, int mili, int& suma) {

    for (int i = 0; i < n; i++) {
        int num = std::rand() % limite;
        std::cout << "Hilo: " << std::this_thread::get_id() << " Aleatorio: " << i << ": " << num << std::endl;
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
    Hilo(int id, std::mutex& m, int n = 5, int tiempo = 1) :id(id), m(m), n(n), tiempo(tiempo) {}

    void operator()() {

        {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "Iniciar el operador(" << id << ") con getId: " << std::this_thread::get_id() << std::endl;
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
            std::cout << "Termina el operador(" << id << ")" << std::endl;
        }
    }
};

int main()
{
    int suma = 0;

    // Crear el hilo con una funcion:
    /*
    std::thread hiloFuncion{ generarAleatorios, 10, 250, 500, std::ref(suma) };
    
    int nMensajes = 6;
    int ml = 350;

    std::thread hiloLambda([nMensajes, ml]() {
        for (int i = 0; i < nMensajes; i++) {
            std::cout << "mensaje lambda: " << (n + 1) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(ml));
        }
     });*/

    std::mutex m;
    std::vector<std::thread> hilos;

    for (int i = 0; i < 3; i++) {
        std::thread hiloObjeto(Hilo(i, std::ref(m), 1 + std::rand() % 10, std::rand() % 3));
        hilos.push_back(std::move(hiloObjeto));
    }

    for (auto& h : hilos) {
        h.join();
    }
}
