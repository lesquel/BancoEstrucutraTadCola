#pragma once

#include <iostream>
#include "person.hpp"

class BankQueue
{
private:
    Person *arr;          // Arreglo dinámico para almacenar los clientes (Personas)
    int first, last;      // Índices para el primer y el último elemento en la cola
    int capacity;         // Capacidad máxima de la cola
    int size;             // Número actual de elementos en la cola

public:
    /**
     * Constructor por defecto.
     */
    BankQueue() {}

    /**
     * Constructor que inicializa la cola con una capacidad máxima.
     * 
     * @param capacity La capacidad máxima de la cola.
     * 
     * Este constructor inicializa los índices `first` y `last`, y asigna un arreglo dinámico
     * de tamaño `capacity` para almacenar las personas en la cola.
     */
    BankQueue(int capacity)
    {
        this->capacity = capacity;
        arr = new Person[capacity];
        first = -1;
        last = -1;
        size = 0;
    }

    /**
     * Verifica si la cola está vacía.
     * 
     * @return true si la cola está vacía, false en caso contrario.
     */
    bool isEmpty() const { return size == 0; }

    /**
     * Verifica si la cola está llena.
     * 
     * @return true si la cola está llena, false en caso contrario.
     */
    bool isFull() const { return size == capacity; }

    /**
     * Devuelve el tamaño actual de la cola.
     * 
     * @return int Tamaño actual de la cola.
     */
    int sizeCircular() { return size; }

    /**
     * Devuelve el primer cliente en la cola (sin removerlo).
     * 
     * @return Person El primer cliente en la cola.
     * 
     * Si la cola está vacía, devuelve un objeto `Person` vacío y muestra un mensaje de advertencia.
     */
    Person front() const
    {
        if (isEmpty())
        {
            std::cout << "Cola vacía" << std::endl;
            return Person();  // Devuelve un objeto vacío si la cola está vacía
        }
        return arr[first];
    }

    /**
     * Agrega un nuevo cliente a la cola.
     * 
     * @param new_person El cliente que se va a agregar a la cola.
     * 
     * Este método inserta un cliente al final de la cola utilizando un enfoque circular. 
     * Si la cola está llena, se muestra un mensaje de advertencia.
     */
    void enqueue(Person new_person)
    {
        if (isFull())
        {
            std::cout << "Cola llena" << std::endl;
            return;
        }
        if (isEmpty())
        {
            first = 0;  // Si es la primera inserción, `first` apunta al primer elemento
        }
        last = (last + 1) % capacity;  // Avanza de forma circular en el arreglo
        arr[last] = new_person;
        size++;
    }

    /**
     * Elimina y devuelve el primer cliente de la cola.
     * 
     * @return Person El primer cliente removido de la cola.
     * 
     * Este método elimina al cliente en la posición `first` de la cola y ajusta los índices
     * de manera circular. Si la cola está vacía, devuelve un objeto `Person` vacío.
     */
    Person dequeue()
    {
        if (isEmpty())
        {
            std::cout << "Cola vacía" << std::endl;
            return Person();  // Devuelve un objeto vacío si la cola está vacía
        }
        Person person = arr[first];  // Almacena temporalmente el cliente que se va a eliminar
        first = (first + 1) % capacity;  // Avanza de forma circular en el arreglo
        size--;

        // Si la cola se vacía después de la operación, restablece los índices
        if (isEmpty())
        {
            first = -1;
            last = -1;
        }
        return person;
    }
};
