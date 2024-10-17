#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "typeOperation.hpp"
#include "bank.hpp"

class Person
{
private:
    std::string name;        // Nombre de la persona
    typeOperation operation; // Operación bancaria que realizará (DEPOSIT o WITHDRAWAL)
    bool elder;              // Indica si la persona es mayor de edad

public:
    // Constructor por defecto
    Person() {}

    // Constructor con parámetros
    Person(std::string name, typeOperation operation, bool elder)
    {
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


    void print_client(){
        cout << "Name: " << name << " | Operation: " << operation << " | Elder: " << elder << endl;
    }
};

// Función para generar clientes aleatorios - Bryan Steven Menoscal Santana
std::vector<Person> generateClients(int numClients)
{
    std::vector<std::string> names = {
        "Juan", "Maria", "Pedro", "Ana", "Luisa", "Robert", "Albert",
        "Jesus", "Carlos", "Diana", "Elena", "Fernando", "Gabriela",
        "Hugo", "Irene", "Jorge", "Karen", "Leonardo", "Marta", "Nicolas"};

    std::vector<Person> clients;
    std::srand(std::time(0));

    for (int i = 0; i < numClients; ++i)
    {
        std::string name = names[rand() % names.size()];

        typeOperation service = static_cast<typeOperation>(rand() % 2 + 3);

        bool isElder = rand() % 2;

        clients.emplace_back(name, service, isElder);
    }

    return clients;
}