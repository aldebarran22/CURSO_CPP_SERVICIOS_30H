#pragma once

#include <crow.h>
#include <unordered_map>
#include <mutex>

class CrowCRUD
{
private:
	std::unordered_map<int, crow::json::rvalue> usuarios;
	int siguiente_id;
	std::mutex mtx;

public:
	CrowCRUD();
	void run();
	~CrowCRUD();
};

