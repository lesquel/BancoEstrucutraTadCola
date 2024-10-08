#pragma once

#include <iostream>
#include <string>
<<<<<<< HEAD
using namespace std;

enum typeOperation
{
    DEPOSITO,
    RETIRO
};
=======
>>>>>>> 8e5f62c210fe0c7a3978bd5bd1b73758a13c1ab7

class Person
{
private:
<<<<<<< HEAD
    std::string name;

    bool priority;
=======
    bool prioridad;      // Corrigiendo la duplicación de nombres
    bool atendido;
    std::string name;
>>>>>>> 8e5f62c210fe0c7a3978bd5bd1b73758a13c1ab7

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
