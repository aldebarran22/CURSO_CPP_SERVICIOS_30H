#pragma once

#include <unordered_map>
#include <crow.h>
#include <mutex>


class CrowCRUD
{

	std::unordered_map<int, crow::json::rvalue>  usuarios;
	int siguiente_id;
	std::mutex mtx;

public:
	CrowCRUD();
	void run();
	~CrowCRUD();
};

