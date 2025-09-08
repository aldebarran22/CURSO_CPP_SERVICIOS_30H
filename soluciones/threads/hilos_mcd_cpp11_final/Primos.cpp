/*
 * Primos.cpp
 *
 *  Created on: 25 oct. 2019
 *      Author: antonio
 */

#include "Primos.h"

Primos::Primos() {
	// TODO Auto-generated constructor stub

}

bool Primos::esPrimo(long numero) {
	int i;

	for (i = 2 ; i < (numero/2)+1 ; i++){
		if (numero % i == 0)
			return false;
	}
	return true;
}

std::vector<int> Primos::calcularPrimos(int n) {
	int i;
	int numero = 2;
	std::vector<int> ptr;

	for (i = 0 ; i < n ; numero++){
		if (esPrimo(numero)){
			ptr.push_back(numero);
			i++;
		}
	}

	return ptr;
}

Primos::~Primos() {
	// TODO Auto-generated destructor stub
}

