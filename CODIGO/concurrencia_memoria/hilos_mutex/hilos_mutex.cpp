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
		std::lock_guard m{ mtx };
		contador_mutex--;

	}
}

int main()
{
	std::mutex mtx;
	std::thread h1{ suma };
	std::thread h2{ resta };

	std::thread h3{ suma_mtx, std::ref(mtx) };
	std::thread h4{ resta_mtx, std::ref(mtx) };

	h1.join();
	h2.join();
	h3.join();
	h4.join();

	std::cout << "Contador: " << contador << std::endl;
	std::cout << "Contador mutex: " << contador_mutex << std::endl;
}
