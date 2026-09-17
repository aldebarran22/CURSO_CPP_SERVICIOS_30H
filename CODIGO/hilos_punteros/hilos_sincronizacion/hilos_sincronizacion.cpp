// hilos_sincronizacion.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#define IT 1000000

int contador = 0;
int contador_mutex = 0;


void suma() {
	std::cout << "Id del this_thread: " << std::this_thread::get_id() << std::endl;
	
	for (int i = 0; i < IT; i++) {
		contador++;
	}
}

void resta() {
	std::cout << "Id del this_thread: " << std::this_thread::get_id() << std::endl;
	
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

void testMutex() {
	std::mutex mtx;

	std::thread h1{ suma };
	std::thread h2{ resta };

	std::thread h3{ suma2, std::ref(mtx) };
	std::thread h4{ resta2, std::ref(mtx) };

	h1.join();
	h2.join();
	h3.join();
	h4.join();

	std::cout << "Id del this_thread: " << std::this_thread::get_id() << std::endl;

	std::cout << "contador:" << contador << std::endl;
	std::cout << "contador_mutex:" << contador_mutex << std::endl;
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
			std::lock_guard<std::mutex> lock(m);
			std::cout << "Operator(" << id << ") " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(tiempo));
		}

		{
			std::lock_guard<std::mutex> lock(m);
			std::cout << "Termina el operador(" << id << ")" << std::endl;
		}
	}
};

void testCrearHilos() {
	std::mutex m;
	std::vector<std::thread> hilos;

	for (int i = 0; i < 3; i++) {
		std::thread hilo(Hilo(i, std::ref(m)));
		hilos.push_back(std::move(hilo));
	}

	for (auto& h : hilos) {
		h.join();
	}
}

int main()
{
	//testMutex();
	testCrearHilos();
}

