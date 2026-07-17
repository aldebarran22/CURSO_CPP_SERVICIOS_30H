#pragma once

#include <unordered_map>
#include <crow.h>
#include <mutex>
#include <string>

class CrowCRUD
{
	// El mapa hace las veces de BD en memoria
	std::unordered_map<int, crow::json::rvalue> usuarios;

	// La clave del mapa
	int siguiente_id; 

	// Para modificar el id de la clave, utilizamos un mutex:
	std::mutex mtx;

public:
	CrowCRUD();
	void run();
	~CrowCRUD();
};

