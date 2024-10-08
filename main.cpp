#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

#include "person.hpp"
#include "caja.hpp"
#include "queue.hpp"

void Desicion(Person &person, Cashier (&caja)[2])
{
    if (!person.getPrioridad()) // Si la persona no tiene prioridad
    {
        for (int i = 0; i < 2; i++)
        {
            if (!caja[i].getOcupado() && !caja[i].getPrioridad()) // Caja sin prioridad
            {
                
                caja[i].Trabajo(person); // Asumimos que la función es Trabajo
                person.setAtendido(true);
                break;
            }
        }
    }
    else // Si la persona tiene prioridad
    {
        for (int i = 0; i < 2; i++)
        {
            if (!caja[i].getOcupado()) // Caja ocupada o no
            {
                caja[i].Trabajo(person); // Asumimos que la función es Trabajo
                person.setAtendido(true);
                break;
            }
        }
    }
}

void Controlador(Queue &cola, Cashier (&caja)[2])
{
    while (!cola.isEmpty())
    {
        Person person = cola.dequeue(); // Consistente con la clase Person

        while (!person.getAtendido()) // Si la persona no ha sido atendida
        {
            Desicion(person, caja);
        }
    }
}

int main()
{
    // creamos la cola de personas
    Queue cola(10);
    cola.enqueue(Person("Mike", false));
    cola.enqueue(Person("Bryan", false));
    cola.enqueue(Person("Jandry", false));
    cola.enqueue(Person("Juan", false));
    cola.enqueue(Person("Pepe", false));
    // creamos las cajas
    Cashier caja[2] = {Cashier(0, 4, false), Cashier(1, 2, true)};

    Controlador(cola, caja);
    return 0;
}

