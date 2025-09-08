/*
 * principal.cpp
 *
 *  Created on: 25 oct. 2019
 *      Author: antonio
 */



#include <thread>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

class Hilo {

	int n;
	int tiempo;

public:
	Hilo(int n=5, int tiempo=1):n(n),tiempo(tiempo){}
	void operator()(){
		for (int i = 0 ; i < this->n ; i++){
			std::cout << "Operator () mensaje " << (i+1) << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(this->tiempo));
		}
	}
	~Hilo(){}
};

void generarAleatorios(int n, int limite, int mili, int &suma){
	int num;
	suma = 0;

	for (int i = 0 ; i < n ; i++){
		num = std::rand()%limite;
		suma += num;
		std::cout << num << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(mili));
	}
}


int main(){
	int it = 12;
	int ml = 150;
	std::srand(time(0));
	Hilo obj(10, 2);
	int suma;
	std::thread hiloFuncion {generarAleatorios, 10, 250, 500, std::ref(suma)};
	std::thread hiloObjeto( obj );
	std::thread hiloLambda([it,ml](){
		for (int i = 0 ; i < it ; i++){
			std::cout << "mensaje lambda: " << (i+1) << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(ml));
		}
	});
	hiloFuncion.join();
	hiloObjeto.join();
	hiloLambda.join();
	std::cout << "La suma de aleatorios es: " << suma << std::endl;
}
