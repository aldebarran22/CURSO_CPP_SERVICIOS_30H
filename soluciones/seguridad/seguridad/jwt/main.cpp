// jwt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "jwt-cpp/jwt.h"

void testJwt() {
    // Prueba para generar un JWT:
    const std::string pass = "una clave secreta";

    auto token = jwt::create()
        .set_issuer("Antonio")
        .set_type("JWT")
        .set_payload_claim("nombre", jwt::claim(std::string("Antonio")))
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes{ 5 })
            .sign(jwt::algorithm::hs256{ pass });

    std::cout << "Token generado:\n" << token << std::endl;
    auto decoded = jwt::decode(token);

    std::cout << "Contenido del token:\n";
    auto json = decoded.get_payload_json();
    for (const auto& [key, value] : json) {
        std::cout << key << ": " << value.to_str() << "\n";
    }
}

int main()
{
    testJwt();
    return 0;
}

