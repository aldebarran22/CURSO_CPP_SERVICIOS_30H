// hilos_join.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <thread>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

class Hilo {

	int n;
	int tiempo;

public:
	Hilo(int n = 5, int tiempo = 1) :n(n), tiempo(tiempo) {}
	void operator()() {
		for (int i = 0; i < this->n; i++) {
			std::cout << "Operator () mensaje " << (i + 1) << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(this->tiempo));
		}
	}
	~Hilo() {}
};

void generarAleatorios(int n, int limite, int mili, int& suma) {
	int num;
	suma = 0;

	for (int i = 0; i < n; i++) {
		num = std::rand() % limite;
		suma += num;
		std::cout << num << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(mili));
	}
}






int main()
{
    std::cout << "Hello World!\n";
}
