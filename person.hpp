#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "typeOperation.hpp"
#include "bank.hpp"

class Person
{
private:
    std::string name;
    typeOperation operation;
    bool elder;

public:
    Person(){}
    Person(std::string name, typeOperation operation, bool elder) {
        this->name = name;
        this->operation = operation;
        this->elder = elder;
    }

    std::string getName() const { return name; }
    typeOperation getOperation() const { return operation; }
    bool isElder() const { return elder; }

};