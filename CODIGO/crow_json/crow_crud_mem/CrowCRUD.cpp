#include "CrowCRUD.h"

CrowCRUD::CrowCRUD()
{
	this->siguiente_id = 1;
}

void CrowCRUD::run(){

    crow::SimpleApp app;

    
    CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        // Crear un recurso en el servidor:

        // Recoger el json de la peticion: crow::json::rvalue
        auto body = crow::json::load(req.body);

        // Si  no llega nada:
        if (!body) {
            return crow::response(400, "json incorrecto");
        }

        // Guardar el usuario:
        std::lock_guard<std::mutex> lock(mtx);
        int id = this->siguiente_id++;
        this->usuarios[id] = std::move(body); 

        // Montar la resp: 
        crow::json::wvalue resp;
        resp["id"] = id;

        return crow::response(201, resp);
        
    });

    app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}

CrowCRUD::~CrowCRUD()
{

}
