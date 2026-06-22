#include "CrowCRUD.h"

CrowCRUD::CrowCRUD()
{
	this->siguiente_id = 1;
}

void CrowCRUD::run(){

    crow::SimpleApp app;

    
    CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([]() {
        // Crear un recurso en el servidor:

        
    });

}

CrowCRUD::~CrowCRUD()
{

}
