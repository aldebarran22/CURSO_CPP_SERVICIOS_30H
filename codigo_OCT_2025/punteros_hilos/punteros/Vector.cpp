#include <iostream>
#include <algorithm>
#include <iterator>

#include "Vector.h"

Vector::Vector(int n)
{
	this->n = n;
	this->ocupacion = 0;
	this->numeros = new int[n];
}

Vector::Vector(const Vector&v)
{
	this->n = v.n;
	this->ocupacion = v.ocupacion;
	this->numeros = new int[v.n];

	// Copiar los numeros:
	for (int i = 0; i < v.ocupacion; i++)
		this->numeros[i] = v.numeros[i];
}

Vector& Vector::operator=(const Vector&v)
{
	// ojo, this->numeros ya tenia una reserva:
	delete[] this->numeros;

	this->n = v.n;
	this->ocupacion = v.ocupacion;
	this->numeros = new int[v.n];

	// Copiar los numeros:
	for (int i = 0; i < v.ocupacion; i++)
		this->numeros[i] = v.numeros[i];

	return *this;
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
