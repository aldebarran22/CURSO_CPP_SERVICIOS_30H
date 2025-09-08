/*
 * Primos.h
 *
 *  Created on: 25 oct. 2019
 *      Author: antonio
 */

#ifndef PRIMOS_H_
#define PRIMOS_H_

#include <vector>

class Primos {
public:
	Primos();
	static bool esPrimo(long numero);
	static std::vector<int> calcularPrimos(int n);
	virtual ~Primos();
};

#endif /* PRIMOS_H_ */
