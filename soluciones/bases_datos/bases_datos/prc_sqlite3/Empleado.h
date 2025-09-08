#pragma once
#include <string>

class Empleado
{
private:
	int id;
	std::string nombre;
	std::string cargo;

public:
	Empleado(int=0, std::string="", std::string="");
	int getId() { return this->id; }
	std::string getNombre() { return this->nombre; }
	std::string getCargo() { return this->cargo; }

	void setId(int id) { this->id = id; }
	void setNombre(std::string nombre) { this->nombre = nombre; }
	void setCargo(std::string cargo) { this->cargo = cargo;  }

	std::string to_string() {
		return std::to_string(this->id) + " " + this->nombre + " " + this->cargo;
	}

	~Empleado();
};

