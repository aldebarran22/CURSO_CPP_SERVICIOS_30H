#include <jwt-cpp/jwt.h>
#include <chrono>
#include <string>

#include "CrowCRUD_jwt.h"

CrowCRUD_jwt::CrowCRUD_jwt()
{
	this->siguiente_id = 1;
}

void CrowCRUD_jwt::run() {
    crow::SimpleApp app;

    // Crear una peticion con un token en JWT:
    std::string jwt_secret = "mi clave secreta:123";

    // Ruta para crear el Token:
    CROW_ROUTE(app, "/login").methods("POST"_method)
        ([jwt_secret](const crow::request& req)
            {
                // Recuperar el json enviado de la request:
                auto datos = crow::json::load(req.body);

                // Validar si viene con datos y con el campo usuario:
                if (!datos || !datos.has("usuario"))
                    // 400: Bad request
                    return crow::response(400);

                // Extraer el usuario:
                std::string usuario = datos["usuario"].s();

                // Constructor builder para crear el token jwt:
                auto token = jwt::create()
                    .set_issuer("Antonio")
                    .set_payload_claim("usuario", jwt::claim(usuario))
                    .set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes{ 30 })
                    .sign(jwt::algorithm::hs256{ jwt_secret });

                // Montar la respuesta:
                crow::json::wvalue respuesta;
                respuesta["token"] = token;
                return crow::response(respuesta);
            });

    // Para comprobar el Token:
    CROW_ROUTE(app, "/protegido")
        ([jwt_secret](const crow::request& req) {
        try {
            auto auth = req.get_header_value("Authorization");
            if (auth.substr(0, 7) != "Bearer ")
                return crow::response(401, "Token inválido");

            auto token = auth.substr(7);
            auto decoded = jwt::decode(token);
            
            jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{ jwt_secret })
                .with_issuer("Antonio")
                .verify(decoded);

            std::string usuario = decoded.get_payload_claim("usuario").as_string();
            return crow::response("Acceso concedido a " + usuario);
        }
        catch (const std::exception& e) {
            return crow::response(403, std::string("Error: ") + e.what());
        }
            });

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
