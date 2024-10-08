#pragma once

#include <iostream>
#include <string>
using namespace std;

enum typeOperation
{
    DEPOSITO,
    RETIRO
};

class Person
{
private:
    std::string name;

    bool priority;

public:
    Person(std::string name = "") {
        this->name = name;
    }

    std::string getName() const { return name; }

};