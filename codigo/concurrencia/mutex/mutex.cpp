// mutex.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <thread>
#include <mutex>
#include <iostream>

#define IT 1000000

int contador = 0;
int contador_mutex = 0;


void suma() {
	for (int i = 0; i < IT; i++)
		contador++;
}

void resta() {
	for (int i = 0; i < IT; i++)
		contador--;
}

void suma_mtx(std::mutex& mtx) {
	for (int i = 0; i < IT; i++) {
		mtx.lock();
		contador_mutex++;
		mtx.unlock();
	}
}

void resta_mtx(std::mutex& mtx) {
	for (int i = 0; i < IT; i++) {
		mtx.lock();
		contador_mutex--;
		mtx.unlock();
	}
}

int main()
{
	std::mutex mtx;
	std::thread h1{ suma };
	std::thread h2{ resta };

	h1.join();
	h2.join();

	std::cout << "Contador: " << contador << std::endl;
}
