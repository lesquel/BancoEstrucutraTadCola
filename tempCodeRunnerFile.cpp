#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include "person.hpp"
#include "caja.hpp"
#include "queue.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

mutex mtx; // Mutex global para sincronizar el acceso a las cajas

void Desicion(Person &person, Cashier (&caja)[2])
{
    bool atendido = false;

    while (!atendido) // Repetir hasta que la persona sea atendida
    {
        for (int i = 0; i < 2; i++)
        {
            mtx.lock(); // Bloquear acceso para revisar la caja
            if (!caja[i].getOcupado() && (!person.getPrioridad() || caja[i].getPrioridad() == person.getPrioridad()))
            {
                // Asignamos la persona a la caja
                caja[i].setOcupado(true); // Marca la caja como ocupada
                mtx.unlock(); // Desbloqueamos el mutex antes de llamar a Trabajo

                caja[i].Trabajo(person); // La caja atiende a la persona

                // Después del trabajo, marcamos la caja como libre
                mtx.lock(); // Bloquear para modificar la caja
                caja[i].setOcupado(false);
                mtx.unlock(); // Liberamos el mutex

                person.setAtendido(true); // Marcamos a la persona como atendida
                atendido = true;
                break;
            }
            mtx.unlock(); // Desbloquear si no se puede usar la caja
        }

        // Si no hay cajas disponibles, esperar un poco antes de intentar de nuevo
        if (!atendido)
        {
            sleep_for(milliseconds(100)); // Esperar un breve momento
        }
    }
}

void Controlador(Queue &cola, Cashier (&caja)[2])
{
    vector<thread> threads; // Vector para almacenar los threads

    while (!cola.isEmpty())
    {
        Person person = cola.dequeue(); // Extraemos una persona de la cola
        threads.push_back(thread(Desicion, ref(person), ref(caja))); // Lanzamos un thread para atender a la persona
    }

    // Esperamos a que todos los threads terminen
    for (auto &t : threads)
    {
        if (t.joinable())
            t.join();
    }
}

int main()
{
    // Creamos la cola de personas
    Queue cola(10);
    cola.enqueue(Person("Mike", false));
    cola.enqueue(Person("Bryan", false));
    cola.enqueue(Person("Jandry", false));
    cola.enqueue(Person("Juan", false));
    cola.enqueue(Person("Pepe", false));

    // Creamos las cajas
    Cashier caja[2] = {Cashier(0, 4, false), Cashier(1, 2, true)};

    // Iniciamos el controlador para gestionar las personas y las cajas
    Controlador(cola, caja);

    return 0;
}
