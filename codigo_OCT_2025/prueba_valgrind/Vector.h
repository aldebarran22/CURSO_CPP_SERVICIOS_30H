#pragma once
class Vector
{
private:
	int* numeros;
	int n;
	int ocupacion; // indica el nro. de elementos ocupados

public:
	Vector(int = 10);
	
	// Si no queremos que se puedan utilizar con delete
	//Vector(const Vector&) = delete;
	//Vector& operator=(const Vector&) = delete;

	Vector(const Vector&);
	Vector& operator=(const Vector&);

	bool add(int);
	void imprimir();
	~Vector();
};

