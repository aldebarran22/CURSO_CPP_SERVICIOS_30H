
/*

Hilos en CPP 11

Aqui se detallan las 3 formas que tenemos de crear hilos en C++ 11
Con punteros a funcion,
Con objetos funcion y sobrecargando el operador ()
Con funciones lambda

*/

#include <iostream>
#include <thread>

// 1 Forma de crear un hilo, con una funcion.
void funcion_hello(){
	int i;

	for (i = 0 ; i < 10 ; i++)
		std::cout << "Hello " << i << std::endl;
}

// 1 Forma de crear el hilo con la funcion, pero inicializando con llaves {}
void funcion_adios(){	
	int i;

	for (i = 0 ; i < 10 ; i++)
		std::cout << "Adios " << i << std::endl;
}



// 2 Forma: Se crea el hilo mediante objeto funcion.
// Para ello se crea una clase que sobrecarga el operador ()

class MiFuncion {

	public:
		void operator()(){
			for (int i = 0 ; i < 10 ; i++)
				std::cout << "Operador () " << i << std::endl;
		}
};


int main(){

	puts("\nLanzar el hilo 1");

	// 1 Forma: Con una funcion
	std::thread h1(funcion_hello);

	std::thread h1b{funcion_adios};

	
	puts("\nLanzar el hilo 2");

	// 2 Forma: Con objetos funcion
	std::thread h2( (MiFuncion()) ); // Ojo, se instancia la clase MiFuncion() se necesitan los parentesis extras.
	
	puts("\nLanzar el hilo 3");

	// 3 Forma: Con funciones lambda
	std::thread h3([]{
		for (int i = 0 ; i < 10 ; i++)
			std::cout << "Lambda " << i << std::endl;
		});

	// Esperar por los 3 hilos
	h1.join();
	h1b.join();
	h2.join();
	h3.join();
	
}
