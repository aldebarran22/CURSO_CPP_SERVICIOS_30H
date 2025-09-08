/*

Lanzar todos los hilos en una coleccion vector 

*/

#include <vector>
#include <algorithm>
#include <thread>
#include <iostream>


class Hilo {

	public:
		void operator()(){
			std::cout << "Dentro del hilo: " << std::this_thread::get_id() << " esta ejecutando" << std::endl;
		}
};


int main(){
	std::vector<std::thread> hilos;

	// Creamos 10 hilos y se añaden al vector:
	for (int i = 0 ; i < 10 ; i++)
		hilos.push_back(std::thread( (Hilo()) ));

	// Ahora esperamos a que acaben todos los hilos:
	std::cout << std::endl << "Esperamos por todos los hilos" << std::endl;

	for (auto &h : hilos)
		h.join();


}
