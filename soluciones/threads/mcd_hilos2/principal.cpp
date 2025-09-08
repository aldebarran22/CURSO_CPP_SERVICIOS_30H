/*
 * principal.cpp
 *
 *  Created on: 24 oct. 2019
 *      Author: antonio
 */

#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <mutex>

#include "Primos.h"

//std::mutex mutex1;

void printVector(std::vector<int> numeros){

	for (auto i : numeros)
		std::cout << i << " ";

	std::cout << std::endl;
}

void factorizar(int numero, std::vector<int> & factores, const std::vector<int> &primos, std::mutex &mutex1){
	int numPrimos;
	int iPrimo = 0;
	int primo, factor;

	mutex1.lock();
	numPrimos = primos.size();
	mutex1.unlock();

	while (numero > 1 && iPrimo < numPrimos){

		mutex1.lock();
		primo = primos.at(iPrimo);
		mutex1.unlock();

		if (numero % primo == 0){
			numero = numero / primo;
			factor = primo;

			// Añadir el factor:
			factores.push_back(factor);

		} else
			// Probar con el siguiente primo:
			iPrimo++;
	}
}

int fun_mcd(std::vector<int> factores1, std::vector<int> factores2){
	int mcd = 1;
	unsigned int i;
	int exponente;
	int cuenta1, cuenta2;

	for (i = 0 ; i < factores1.size() ; ){

		cuenta1 = std::count(factores1.begin(), factores1.end(), factores1.at(i));
		cuenta2 = std::count(factores2.begin(), factores2.end(), factores1.at(i));

		//std::cout << "\nBuscar factor:" << factores1.at(i) << " cuenta1: " << cuenta1 <<  " cuenta2: " << cuenta2 << std::endl;
		if (cuenta1 > 0 && cuenta2 > 0){

			// Hay un factor comun
			exponente = (cuenta1 < cuenta2) ? cuenta1 : cuenta2;
			mcd *= std::pow(factores1.at(i), exponente);
		}

		// Salta tantas posiciones como veces se repita el numero:
		i+= cuenta1;
	}

	return mcd;
}


int main(){
	std::vector<int> primos;
	std::vector<int> factores1, factores2;
	int numero1 = 720, numero2 = 864;

	// Calcular los primos:
	primos = Primos::calcularPrimos(MAX_NUM_PRIMOS);
	std::cout << MAX_NUM_PRIMOS << " primos:" << std::endl;
	printVector(primos);

	// Crear los hilos:
	std::mutex mutex1;
	std::thread h1(factorizar, numero1, std::ref(factores1), primos, std::ref(mutex1));
	std::thread h2(factorizar, numero2, std::ref(factores2), primos, std::ref(mutex1));

	if (h1.joinable()) h1.join();
	if (h2.joinable()) h2.join();


	std::cout << "\nNumero: " << numero1 << std::endl;
	printVector(factores1);

	std::cout << "\nNumero: " << numero2 << std::endl;
	printVector(factores2);

	std::cout << std::endl << "MCD: " << fun_mcd(factores1, factores2) << std::endl;

}
