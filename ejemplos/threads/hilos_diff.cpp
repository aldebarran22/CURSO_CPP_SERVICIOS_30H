/*

Diferenciar entre hilos. Nos referimos a hilos creados a partir de main y al hilo principal.

Dentro de la funcion del hilo, hacemos referencia a este, mediante: std::this_thread::get_id()

*/ 


#include <thread>
#include <iostream>


void thread_funcion(){

	std::cout << "\nDentro de la funcion del hilo. El id es: " << std::this_thread::get_id() << std::endl;
}

int main(){

	std::thread h1(thread_funcion);
	std::thread h2(thread_funcion);

	// Comparar los ids de los threads, deberian ser iguales?

	if (h1.get_id() != h2.get_id())
		std::cout << "\nAmbos threads tienen el mismo ID\n" << std::endl;

	
	// Imprimir los ids dentro del main:
	std::cout << "\nID del thread 1: " << h1.get_id() << std::endl;
	std::cout << "\nID del thread 2: " << h2.get_id() << std::endl;

	h1.join();
	h2.join();
}
