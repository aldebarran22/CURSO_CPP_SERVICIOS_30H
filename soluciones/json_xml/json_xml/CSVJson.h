#pragma once
#include <string>

class CSVJson
{
public:
	static void conversorCSVToJson(std::string ficheroCSV, std::string ficheroJSON);
	static void conversorJsonCSV(std::string ficheroJSON);	
};

