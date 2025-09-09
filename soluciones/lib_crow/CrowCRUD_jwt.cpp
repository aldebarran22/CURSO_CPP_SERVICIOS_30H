#include <jwt-cpp/jwt.h>

#include "CrowCRUD_jwt.h"

CrowCRUD_jwt::CrowCRUD_jwt()
{
	this->siguiente_id = 1;
}

void CrowCRUD_jwt::run() {
    crow::SimpleApp app;

    // CREATE - POST /usuarios
    CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "JSON inválido");

        std::lock_guard<std::mutex> lock(mtx);
        int id = siguiente_id++;
        usuarios[id] = body;

        crow::json::wvalue res;
        res["id"] = id;
        return crow::response(201, res);
        });

    // READ - GET /usuarios/<id>
    CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
        std::lock_guard<std::mutex> lock(this->mtx);

        std::cout << "Tenemos " << usuarios.count(id) << " usuarios. " << std::endl;

        if (usuarios.count(id) == 0) return crow::response(404, "Usuario no encontrado");
        crow::json::wvalue res;
        res["nombre"] = usuarios[id]["nombre"].s();
        res["email"] = usuarios[id]["email"].s();
        return crow::response(res);
        });

    // UPDATE - PUT /usuarios/<id>
    CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request& req, int id) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "JSON inválido");

        std::lock_guard<std::mutex> lock(this->mtx);
        if (usuarios.count(id) == 0) return crow::response(404, "Usuario no encontrado");

        usuarios[id] = body;
        return crow::response(200, "Usuario actualizado");
        });

    // DELETE - DELETE /usuarios/<id>
    CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {
        std::lock_guard<std::mutex> lock(this->mtx);
        if (usuarios.erase(id) == 0)
            return crow::response(404, "Usuario no encontrado");

        crow::response res;
        res.code = 204;
        return res;
        });


    CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {
        std::lock_guard<std::mutex> lock(this->mtx);

        crow::json::wvalue lista = crow::json::wvalue::list();
        int i = 0;

        for (const auto& [id, usuario] : usuarios) {
            crow::json::wvalue item;
            item["id"] = id;

            if (usuario.has("nombre"))
                item["nombre"] = usuario["nombre"].s();
            else
                item["nombre"] = "";

            if (usuario.has("email"))
                item["email"] = usuario["email"].s();
            else
                item["email"] = "";

            lista[i++] = std::move(item);  // ✅ Añadir al array por índice
        }

        crow::json::wvalue res;
        res["usuarios"] = std::move(lista);
        return crow::response(res);
        });


    app.port(8081).multithreaded().run();

}

CrowCRUD_jwt::~CrowCRUD_jwt()
{
}
