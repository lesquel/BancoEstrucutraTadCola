#pragma once

#include "person.hpp"

class Caja
{
private:
    Person person;
    int number;
    bool occupied;
    int waitingTime;
    bool priority;

public:
    Caja(Person person, int number, bool occupied, int waitingTime, bool priority)
    {
        this->person = person;
        this->number = number;
        this->occupied = occupied;
        this->waitingTime = waitingTime;
        this->priority = priority;
    }

    Person getPerson() const { return person; }
    int getnumber() const { return number; }
    bool getoccupied() const { return occupied; }
    int getTiempoDeEspera() const { return waitingTime; }
    bool getpriority() const { return priority; }
};

