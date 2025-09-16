#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/types.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <iostream>

int main() {
    // Inicializa la instancia global de MongoDB (solo una vez por aplicación)
    mongocxx::instance instance{};

    try {
        // Conexión al servidor local
        mongocxx::client client{ mongocxx::uri{"mongodb://localhost:27017"} };

        // Accede a la base de datos y colección
        auto db = client["bdwebs"];
        auto collection = db["webs"];

        // Inserta un documento
        bsoncxx::document::value doc = bsoncxx::builder::stream::document{}
            << "nombre" << "VisualStudioTest"
            << "navegador" << "Edge"
            << "fecha" << bsoncxx::types::b_date{ std::chrono::system_clock::now() }
        << bsoncxx::builder::stream::finalize;

        collection.insert_one(doc.view());

        // Consulta y muestra los documentos
        auto cursor = collection.find({});
        for (auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }

    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
