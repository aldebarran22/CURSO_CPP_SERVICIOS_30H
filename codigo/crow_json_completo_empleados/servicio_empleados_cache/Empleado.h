#pragma once

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Empleado {
public:
    int id;
    std::string nombre, cargo;


    std::string to_string() const {
        return std::to_string(id) + " " + nombre + " " + cargo;
    }
};

// fuera de la clase, en el mismo namespace
inline void to_json(json& j, const Empleado& e) {
    j = json{
        {"id", e.id},
        {"nombre", e.nombre},
        {"cargo", e.cargo}
    };
}

inline void from_json(const json& j, Empleado& e) {
    j.at("id").get_to(e.id);
    j.at("nombre").get_to(e.nombre);
    j.at("cargo").get_to(e.cargo);
}
