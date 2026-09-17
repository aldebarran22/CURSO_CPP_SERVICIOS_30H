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

void suma2(std::mutex& mtx) {
	for (int i = 0; i < IT; i++) {
		mtx.lock();
		contador_mutex++;
		mtx.unlock();
	}
}

void resta2(std::mutex& mtx) {
	for (int i = 0; i < IT; i++) {
		std::lock_guard m{ mtx };
		contador_mutex--;
	}
}

int main()
{
	std::mutex mtx;

	std::thread h1{ suma };	
	std::thread h2{ resta };
    
	std::thread h3{ suma2, std::ref(mtx)};
	std::thread h4{ resta2, std::ref(mtx)};

	h1.join();
	h2.join();
	h3.join();
	h4.join();

	std::cout << "contador:" << contador << std::endl;
	std::cout << "contador_mutex:" << contador_mutex << std::endl;
}

