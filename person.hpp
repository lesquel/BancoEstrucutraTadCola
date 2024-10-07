#pragma once

#include <iostream>

class Person
{
private:
    std::string name;
    // int edad;
    // std::string direccion;
    bool priority;

public:
    Person(std::string name = "") {
        this->name = name;
    }

    std::string getName() const { return name; }
    // int getEdad() const { return edad; }
    // std::string getDireccion() const { return direccion; }
};

