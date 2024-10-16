#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib> // Para system()

#include "bankQueue.hpp"
#include "bankTeller.hpp"
#include "person.hpp"

class Bank
{
private:
    std::string bankName;                // Nombre del banco
    BankQueue normalQueue;               // Cola de clientes regulares
    BankQueue prioritaryQueue;           // Cola de clientes prioritarios (por ejemplo, ancianos)
    std::vector<BankTeller> bankTellers; // Vector que almacena los cajeros del banco
    std::mutex queueMutex;               // Mutex para controlar el acceso concurrente a las colas
    int QUEUECAPACITY = 40;              // Capacidad máxima de las colas de clientes

public:
    /**
     * Constructor de la clase Bank.
     *
     * @param bankName Nombre del banco.
     *
     * Este constructor inicializa las colas de clientes (normal y prioritaria)
     * y añade tres cajeros al banco, uno para depósitos, uno para retiros y uno
     * para ambos servicios (depósitos y retiros).
     */
    Bank(std::string bankName)
    {
        this->bankName = bankName;                                  // Nombre del banco
        this->normalQueue = BankQueue(QUEUECAPACITY);               // Cola de clientes regulares
        this->prioritaryQueue = BankQueue(QUEUECAPACITY);           // Cola de clientes prioritarios
        bankTellers.emplace_back(BankTeller("Deposito", DEPOSIT));  // Cajero especializado en depósitos
        bankTellers.emplace_back(BankTeller("Retiro", WITHDRAWAL)); // Cajero especializado en retiros
        bankTellers.emplace_back(BankTeller("Especial", BOTH));     // Cajero que maneja tanto depósitos como retiros
        // bankTellers.emplace_back(BankTeller("Especial2", BOTH));     // Cajero que maneja tanto depósitos como retiros
    }

    void addClient(Person client)
    {
        if (client.isElder())
        {
            prioritaryQueue.enqueue(client);
        }
        else
        {
            normalQueue.enqueue(client);
        }
    }

    void PrintPersons()
    {
        std::cout << "Priority Queue:" << std::endl;

        // Crear una copia para no modificar la cola original
        BankQueue tempQueue = prioritaryQueue;

        while (!tempQueue.isEmpty())
        {
            Person person = tempQueue.dequeue(); // Extraer el elemento
            std::cout << person.getName() << " ";
        }

        std::cout << "\n Normal Queue:" << std::endl;
        tempQueue = normalQueue;
        
        while (!tempQueue.isEmpty())
        {
            Person person = tempQueue.dequeue(); // Extraer el elemento
            std::cout << person.getName()<< " ";
        }
    }

    /**
     * Inicia el servicio de los cajeros.
     *
     * Este método maneja el proceso de atender a los clientes en paralelo mediante hilos.
     * Los cajeros atienden a los clientes, dando prioridad a la cola de clientes prioritarios.
     * Si la cola prioritaria está vacía, los cajeros atienden a los clientes de la cola normal.
     *
     * Se utiliza un mutex (`queueMutex`) para asegurar que solo un cajero acceda a una cola
     * al mismo tiempo, evitando condiciones de carrera. El proceso continúa hasta que todas
     * las colas están vacías y todos los clientes han sido atendidos.
     */
    void startService()
    {
        std::vector<std::thread> threads; // Vector para almacenar los hilos de cajeros

        // Mientras haya clientes en cualquiera de las colas
        while (!normalQueue.isEmpty() || !prioritaryQueue.isEmpty())
        {
            threads.clear(); // Limpia el vector de hilos para el siguiente ciclo

            // Atender a la cola prioritaria con la caja especial si hay clientes en la cola prioritaria

            PrintPersons();

            if (!prioritaryQueue.isEmpty())
            {
                threads.emplace_back(std::thread([this, &teller = bankTellers[2]]
                                                 { teller.serveClient(prioritaryQueue, queueMutex); }));
            }
            else if (!normalQueue.isEmpty())
            {
                // Si la cola prioritaria está vacía, atiende de la cola normal
                threads.emplace_back(std::thread([this, &teller = bankTellers[2]]
                                                 { teller.serveClient(normalQueue, queueMutex); }));
            }

            // Atender a los clientes normales con los otros cajeros
            for (size_t i = 0; i < bankTellers.size(); ++i)
            {
                if (i != 2) // Asegurarse de que no se use la caja especial para clientes normales
                {
                    // Si la cola normal está vacía, atiende de la cola prioritaria
                    if (normalQueue.isEmpty() && !prioritaryQueue.isEmpty())
                    {
                        threads.emplace_back(std::thread([this, &teller = bankTellers[i]]
                                                         { teller.serveClient(prioritaryQueue, queueMutex); }));
                    }
                    else if (!normalQueue.isEmpty()) // Si hay clientes normales, atiende de la cola normal
                    {
                        threads.emplace_back(std::thread([this, &teller = bankTellers[i]]
                                                         { teller.serveClient(normalQueue, queueMutex); }));
                    }
                }
            }

            // Espera a que todos los hilos terminen de atender a sus respectivos clientes
            for (auto &thread : threads)
            {
                thread.join(); // Unir todos los hilos
            }

            system("cls"); // Limpia la consola
        }

        std::cout << "Todos los clientes han sido atendidos." << std::endl;
    }
};
