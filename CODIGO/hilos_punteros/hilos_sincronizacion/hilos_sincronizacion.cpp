// hilos_sincronizacion.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <mutex>
#include <thread>

#define IT 1000000

int contador = 0;
int contador_mutex = 0;


void suma() {
	for (int i = 0; i < IT; i++) {
		contador++;
	}
}

void resta() {
	for (int i = 0; i < IT; i++) {
		contador--;
	}
}

int main()
{
	std::mutex mtx;
	std::thread h1{ suma };
	std::thread h2{ resta };
    
	h1.join();
	h2.join();

	std::cout << "contador:" << contador << std::endl;
}

