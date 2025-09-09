#pragma once

#include <crow.h>
#include <unordered_map>
#include <mutex>

class CrowCRUD_jwt
{
private:
	std::unordered_map<int, crow::json::rvalue> usuarios;
	int siguiente_id;
	std::mutex mtx;

public:
	CrowCRUD_jwt();
	void run();
	~CrowCRUD_jwt();

};

