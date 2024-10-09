#pragma once

#include <iostream>
#include "person.hpp"

class BankQueue
{
private:
    Person *arr;
    int first, last, capacity, size;

public:
    BankQueue() {}
    BankQueue(int capacity)
    {
        this->capacity = capacity;
        arr = new Person[capacity];
        first = -1;
        last = -1;
        size = 0;
    }

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }
    int sizeCircular() { return size; }
    Person front() const 
    {
        if (isEmpty())
        {
            std::cout << "Cola vacia" << std::endl;
            return Person();
        }
        return arr[first];
    }

    void enqueue(Person new_person)
    {
        if (isFull())
        {
            std::cout << "Cola llena" << std::endl;
            return;
        }
        if (isEmpty())
        {
            first = 0;
        }
        last = (last + 1) % capacity;
        arr[last] = new_person;
        size++;
    }

    Person dequeue()
    {
        if (isEmpty())
        {
            std::cout << "Cola vacia" << std::endl;
            return Person();
        }
        Person person = arr[first];
        first = (first + 1) % capacity;
        size--;
        if (isEmpty())
        {
            first = -1;
            last = -1;
        }
        return person;
    }
};