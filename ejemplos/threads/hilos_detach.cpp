
/* 

	Ejemplo de un hilo llamando a detach

*/

#include <thread>
#include <iostream>
#include <chrono>

void hiloIndependiente(){

	std::cout << "Iniciando hilo independiente ..." << std::endl;
	//for (int i = 0 ; i < 5 ; i++){
	//	std::cout << "Realizando trabajo ... " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	//}
	std::cout << "Saliendo del hilo independiente" << std::endl;
}

void hiloLlamante(){

	std::cout << "Iniciando el hilo llamante ..." << std::endl;
	
	// Creamos un hilo:
	std::thread t(hiloIndependiente);
	t.detach();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Saliendo del hilo llamante ..." << std::endl;
}

int main(){

	hiloLlamante();
	std::cout << "Hilo main() para 5 sg." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "Hilo main() finaliza." << std::endl;
}
