#pragma once

#include <string>

class CSVXml
{
public:
	static void conversorCSVToXml(std::string ficheroCSV, std::string ficheroXML);
	static void conversorXmlCSV(std::string ficheroXML);
};

