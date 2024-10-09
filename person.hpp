#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "typeOperation.hpp"
#include "bank.hpp"

class Person
{
private:
    std::string name;          // Nombre de la persona
    typeOperation operation;   // Operación bancaria que realizará (DEPOSIT o WITHDRAWAL)
    bool elder;                // Indica si la persona es mayor de edad

public:
    // Constructor por defecto
    Person(){}

    // Constructor con parámetros
    Person(std::string name, typeOperation operation, bool elder) {
        this->name = name;
        this->operation = operation;
        this->elder = elder;
    }

    // Obtener el nombre de la persona
    std::string getName() const { return name; }

    // Obtener el tipo de operación (DEPOSIT o WITHDRAWAL)
    typeOperation getOperation() const { return operation; }

    // Verificar si la persona es mayor
    bool isElder() const { return elder; }
};
