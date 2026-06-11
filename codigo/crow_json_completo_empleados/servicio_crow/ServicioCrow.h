#pragma once

#include <crow.h>
#include <unordered_map>
#include <mutex>

class ServicioCrow
{
	int siguiente_id;
	std::mutex mutex;
	std::unordered_map<int, crow::json::rvalue> usuarios;

public:
	ServicioCrow();
	void run();
	~ServicioCrow();
};

