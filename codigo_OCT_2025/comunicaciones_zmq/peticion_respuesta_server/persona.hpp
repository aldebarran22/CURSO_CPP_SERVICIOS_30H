// persona.hpp
#pragma once
#include <string>
#include <nlohmann/json.hpp>

struct Persona {
    std::string nombre;
    int edad;
    bool activo;
};

inline void to_json(nlohmann::json& j, const Persona& p) {
    j = nlohmann::json{ {"nombre", p.nombre}, {"edad", p.edad}, {"activo", p.activo} };
}

inline void from_json(const nlohmann::json& j, Persona& p) {
    j.at("nombre").get_to(p.nombre);
    j.at("edad").get_to(p.edad);
    j.at("activo").get_to(p.activo);
}
