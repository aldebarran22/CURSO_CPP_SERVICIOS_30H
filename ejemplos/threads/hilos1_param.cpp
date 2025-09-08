/*

Para pasar argumentos a un hilo, se definen los parametros de entrada a la funcion
Y cuando indicamos al hilo el nombre de la funcion a ejecutar, se le pasan los n parametros
	
*/


#include <iostream>
#include <thread>
#include <string>

void funcion(int x, std::string s){

	std::cout << "Parametro int: " << x << std::endl;
	std::cout << "Parametro string: " << s << std::endl;
}


int main(){
	std::thread hilo(funcion, 1, std::string("hola")); // Para convertir mejor a string en vez const char * y que lo convierta automatico
	hilo.join();
}
