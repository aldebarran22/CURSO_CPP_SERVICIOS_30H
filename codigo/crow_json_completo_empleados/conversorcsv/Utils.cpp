#include "Utils.h"

#include <sstream>

void Utils::split(const std::string& linea, char delim, std::vector<std::string>& campos)
{
	std::stringstream ss;

	ss.str(linea);
	std::string item;
	while (std::getline(ss, item, delim)) {
		campos.push_back(item);
	}
}
