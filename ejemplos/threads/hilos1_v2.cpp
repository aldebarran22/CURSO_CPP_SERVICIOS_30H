/*

Hilos en CPP 11


*/

#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>

void hello(){

	for (int i = 0 ; i < 5 ; i++)
		std::cout << "Hello" << std::endl;
}


void numeros(){
	srand(time(NULL));

	for (int i = 0 ; i < 10 ; i++)
		std::cout << rand()%100 << std::endl;	

} 

int main(){
	
	// Al crear los hilos se indica la funcion que tienen que ejecutar
	std::thread h1(hello);
	std::thread h2(numeros);

	h1.join();	
	h2.join();	
}
