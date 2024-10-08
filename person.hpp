#pragma once

#include <iostream>
#include <string>
using namespace std;


class Person
{
private:
    string nombre;
    int edad;
    string direccion;
    bool prioridad;
    bool atendido;
    std::string name;
    bool priority;

public:
    Person(std::string name = "") {
        this->name = name;
    }

    std::string getName() const { return name; }

};