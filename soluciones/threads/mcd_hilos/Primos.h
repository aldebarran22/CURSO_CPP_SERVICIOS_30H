/*
 * Primos.h
 *
 *  Created on: 24 oct. 2019
 *      Author: antonio
 */

#ifndef PRIMOS_H_
#define PRIMOS_H_

#define MAX_NUM_PRIMOS 100

#include <vector>

class Primos {
public:
	Primos();
	static bool esPrimo(int numero);
	static std::vector<int> calcularPrimos(int n);
	virtual ~Primos();
};

#endif /* PRIMOS_H_ */
