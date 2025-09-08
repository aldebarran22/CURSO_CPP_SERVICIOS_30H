/*
 * principal.cpp
 *
 *  Created on: 25 oct. 2019
 *      Author: antonio
 */

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

#include "Primos.h"

#define PRIMOS 100


void printVector(std::vector<int> v){
	for (auto i : v)
		std::cout << i << " ";

	std::cout << std::endl;
}


void factorizar2Numeros(int numero, std::vector<int> &factores, const std::vector<int> &primos, std::mutex &mtx){
	int numPrimos;
	int iPrimo = 0;
	int primo, factor;

		mtx.lock();
		numPrimos = primos.size();
		mtx.unlock();

		while (numero > 1 && iPrimo < numPrimos){
			mtx.lock();
			primo = primos.at(iPrimo);
			mtx.unlock();

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


void factorizar(int numero, std::map<int, std::vector<int> > &grupoFactores,
		const std::vector<int> &primos, std::mutex &mtxPrimos, std::mutex &mtxFactores){
	int numPrimos;
	int iPrimo = 0;
	int primo, factor;
	std::vector<int> factores;
	int claveNumero = numero;

	mtxPrimos.lock();
	numPrimos = primos.size();
	mtxPrimos.unlock();

	while (numero > 1 && iPrimo < numPrimos){
		mtxPrimos.lock();
		primo = primos.at(iPrimo);
		mtxPrimos.unlock();

		if (numero % primo == 0){
			numero = numero / primo;
			factor = primo;

			// Añadir el factor:
			factores.push_back(factor);

		} else
			// Probar con el siguiente primo:
			iPrimo++;
	}

	// Se van almacenando los factores de cada numero.
	mtxFactores.lock();
	grupoFactores[claveNumero] = factores;
	mtxFactores.unlock();
}


int mcd(std::vector<int> d1, std::vector<int> d2){
	int mcd = 1;
	int exponente;
	int cuenta1, cuenta2;

	for (unsigned i = 0 ; i < d1.size() ; ){

		cuenta1 = std::count(d1.begin(), d1.end(), d1.at(i));
		cuenta2 = std::count(d2.begin(), d2.end(), d1.at(i));

		if (cuenta1 > 0 && cuenta2 > 0){

			// Hay un factor comun
			exponente = (cuenta1 < cuenta2) ? cuenta1 : cuenta2;
			mcd *= std::pow(d1.at(i), exponente);
		}

		// Salta tantas posiciones como veces se repita el numero:
		i+= cuenta1;
	}

	return mcd;
}

int mcd(std::map<int, std::vector<int> > grupoFactores){
	// Toma los factores del primer numero y los va comparando con el resto.
	int mcd = 1;
	std::vector<int> factores1;
	std::map<int, std::vector<int>>::iterator it;
	int cuentaComun, cuenta1, cuentaAux, factorABuscar;
	bool esUnFactorComun;
	//std::set<int> claves = getClavesMapa(grupoFactores);
	bool primero;

	std::cout << "\n\nCalculo del MCD, para " << grupoFactores.size() << " números" << std::endl;
	it = grupoFactores.begin();
	factores1 = it->second;

	for (unsigned i = 0 ; i < factores1.size() ; ){
		factorABuscar = it->second.at(i);
		cuenta1 = std::count(factores1.begin(), factores1.end(), factorABuscar);
		cuentaComun = cuenta1;
		esUnFactorComun = true;
		primero = true;

		//std::cout << "El primer factor es: " << factorABuscar << std::endl;
		//std::cout << "Se repite: " << cuenta1 << std::endl;

		// Compara la cuenta con el resto de factores: Salta el primero
		for (auto [key, factores] : grupoFactores){

			// Saltar el primer grupo de factores, es el que se utiliza para buscar ...
			if (primero){
				primero = false;
				continue;
			}

			// Contar las repeticiones en el resto de factores:
			cuentaAux = std::count(factores.begin(), factores.end(), factorABuscar);

			if (cuentaAux == 0){
				// Si no ha encontrado el factor corta:
				esUnFactorComun = false;
				break;

			} else {
				if (cuentaAux < cuentaComun)
					cuentaComun = cuentaAux;
			}
		}
		// Salta tantas posiciones como veces se repita el numero:
		i+= cuenta1;

		if (esUnFactorComun){
			std::cout << factorABuscar << "^" << cuentaComun << "  ";
			mcd *= std::pow(factorABuscar, cuentaComun);
		}


	}
	return mcd;
}



void test2Numeros(const std::vector<int> &primos){
	int numero1 = 720;
	int numero2 = 864;
	std::mutex mtx;
	std::vector<int> factores1, factores2;

	std::thread h1(factorizar2Numeros, numero1, std::ref(factores1), primos, std::ref(mtx));
	std::thread h2(factorizar2Numeros, numero2, std::ref(factores2), primos, std::ref(mtx));

	h1.join();
	h2.join();

	std::cout << "\nNumero1: " << numero1 << std::endl;
	printVector(factores1);

	std::cout  << "\nNumero2: " << numero2 << std::endl;
	printVector(factores2);

	std::cout << "\nM.C.D. " << mcd(factores1, factores2) << std::endl;

}


void testVectorNumeros(const std::vector<int> &primos){
	// A partir de un vector de numeros generar tantos hilos como números. Cada hilo factoriza un numero.
	std::vector<int> numeros = {7200, 8640, 600, 1320, 1440};
	std::vector<std::thread> grupoHilos;
	std::map<int, std::vector<int> > grupoFactores;
	std::mutex mtx, mtxFactores;
	int valorMCD;

	auto iniT = std::chrono::system_clock::now(); // El instante actual:

	for (auto numero : numeros){
		std::cout << "Creando hilo para el número: " << numero << std::endl;
		grupoHilos.push_back(std::thread(factorizar, numero, std::ref(grupoFactores), primos, std::ref(mtx), std::ref(mtxFactores)));
	}

	for (auto &hilo : grupoHilos)
		hilo.join();

	valorMCD = mcd(grupoFactores);

	auto finT = std::chrono::system_clock::now(); // El instante actual:

	std::chrono::duration<float, std::milli> tiempoEjecucion = finT - iniT;
	std::cout << "\n\nFactores para " << grupoFactores.size() << " numeros" << std::endl;
	for (auto [num, fact] : grupoFactores){
		std::cout << "\nNúmero: " << num << std::endl << "Factores: ";
		printVector(fact);
	}

	std::cout << "\n\nM.C.D. --> " << valorMCD << std::endl;
	std::cout << "\nTiempo total: " <<  tiempoEjecucion.count()/1000.0 << " sg. " << std::endl;
}



int main(){
	std::vector<int> primos = Primos::calcularPrimos(PRIMOS);
	std::cout << "PRIMOS:" << std::endl;
	printVector(primos);
	std::cout << std::endl;

	//test2Numeros(primos);
	testVectorNumeros(primos);
}
