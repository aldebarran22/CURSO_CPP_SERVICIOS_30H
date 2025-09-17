#pragma once
#include <string>

struct Empleado {
    int id;
    std::string nombre;
    std::string cargo;

    std::string serialize() const {
        return std::to_string(id) + "|" + nombre + "|" + cargo;
    }

    static Empleado deserialize(const std::string& data) {
        size_t p1 = data.find('|');
        size_t p2 = data.find('|', p1 + 1);
        return {
            std::stoi(data.substr(0, p1)),
            data.substr(p1 + 1, p2 - p1 - 1),
            data.substr(p2 + 1)
        };
    }
};
