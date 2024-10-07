#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

#include "person.hpp"
#include "caja.hpp"

void Controlador(Cola &cola, Caja caja[2])
{
    while (!cola.isEmpty())
    {
        Persona person = cola.dequeue();

        while (!person.getAtendido())
        {
            if (!person.getPrioridad())
            {
                for (int i = 0; i < 2; i++)
                {
                    if (!caja[i].getOcupado() && !caja[i].getPrioridad())
                    {
                        caja[i].Tabajo(person);
                        person.setAtendido(true);
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < 2; i++)
                {
                    if (!caja[i].getOcupado())
                    {
                        caja[i].Tabajo(person);
                        person.setAtendido(true);
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    return 0;
}
