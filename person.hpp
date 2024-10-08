#pragma once

#include <iostream>

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