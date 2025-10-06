#pragma once
#include <crow.h>
#include <unordered_map>
#include <mutex>

class CrowCRUD
{
private:
	int siguiente_id;
	std::mutex mtx;
	std::unordered_map<int, crow::json::rvalue> usuarios;

public:
	CrowCRUD();
	void run();
	~CrowCRUD();
};

