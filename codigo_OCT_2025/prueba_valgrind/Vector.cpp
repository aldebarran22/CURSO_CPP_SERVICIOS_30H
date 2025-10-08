#include <iostream>
#include "Vector.h"

Vector::Vector(int n)
{
	this->n = n;
	this->ocupacion = 0;
	this->numeros = new int[n];
}

bool Vector::add(int num)
{
	if (ocupacion + 1 < n) {
		numeros[ocupacion] = num;
		ocupacion++;
		return true;

	}
	return false;
}

void Vector::imprimir()
{
	for (int i = 0; i < ocupacion; i++) {
		std::cout << "i = " << i << " " << numeros[i] << std::endl;
	}
}

Vector::~Vector()
{
	delete[] numeros;
	numeros = nullptr;
}
