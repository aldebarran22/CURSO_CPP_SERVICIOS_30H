#pragma once
class Vector
{
private:
	int* numeros;
	int n;
	int ocupacion; // indica el nro. de elementos ocupados

public:
	Vector(int = 10);
	bool add(int);
	void imprimir();
	~Vector();
};

