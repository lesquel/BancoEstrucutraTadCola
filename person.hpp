#pragma once

#include <iostream>
#include <string>

class Person
{
private:
    bool prioridad;      // Corrigiendo la duplicación de nombres
    bool atendido;
    std::string name;

public:
    Person(std::string name = "", bool prioridad = false)
        : name(name), prioridad(prioridad), atendido(false) // Inicialización correcta de miembros
    {
    }

    std::string getName() const { return name; }
    bool getPrioridad() const { return prioridad; }
    bool getAtendido() const { return atendido; }
    void setAtendido(bool atendido) { this->atendido = atendido; }
};
