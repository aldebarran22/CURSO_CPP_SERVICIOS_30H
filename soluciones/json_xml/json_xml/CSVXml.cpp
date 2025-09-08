#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <libxml/tree.h>

#include "CSVXml.h"
#include "utilidades.h"
#include "pedido.h"


void CSVXml::conversorCSVToXml(std::string ficheroCSV, std::string ficheroXML)
{
    std::ifstream fin(ficheroCSV);
    std::string linea;
    std::vector<std::string> campos;
    bool cabs = true;
    std::vector<xmlNodePtr> array;
      

    if (!fin) {
        std::cerr << "No se ha encontrado el fichero: " << ficheroCSV << std::endl;
        return;
    }

    while (std::getline(fin, linea)) {
               
        if (cabs) {
            cabs = false;

        }
        else {
            Utilidades::split(linea, ';', campos);
            Pedido p(linea);
            array.push_back(p.to_xml());
            campos.clear();           
        }
        
    }
    fin.close();

    // Agregar todos los nodos al documento:
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root = xmlNewNode(nullptr, BAD_CAST "pedidos");
    xmlDocSetRootElement(doc, root);

    for (auto nodo : array) {
        xmlAddChild(root, nodo);
    }

    //  Guardar el archivo:
    xmlSaveFormatFileEnc(ficheroXML.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);

}

void CSVXml::conversorXmlCSV(std::string ficheroXML)
{
}
