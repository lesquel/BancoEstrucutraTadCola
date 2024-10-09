#pragma once

#include <iostream>
#include <vector>
#include <thread>
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
    int QUEUECAPACITY = 20;              // Capacidad máxima de las colas de clientes

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
    }

    /**
     * Retorna la cola de clientes regulares.
     * 
     * @return BankQueue Cola de clientes normales.
     */
    BankQueue getNormalQueue()
    {
        return normalQueue;
    }

    /**
     * Retorna la cola de clientes prioritarios.
     * 
     * @return BankQueue Cola de clientes prioritarios.
     */
    BankQueue getPrioritaryQueue()
    {
        return prioritaryQueue;
    }

    /**
     * Añade un cliente a la cola adecuada.
     * 
     * @param client Cliente a añadir.
     * 
     * Si el cliente es anciano o tiene prioridad (usando `client.isElder()`),
     * se añade a la cola prioritaria. De lo contrario, se añade a la cola normal.
     */
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
            // Asigna trabajo a cada cajero disponible
            for (auto &teller : bankTellers)
            {
                // Si la cola prioritaria no está vacía, asigna un cliente de esa cola
                if (!prioritaryQueue.isEmpty())
                    threads.emplace_back(std::thread(&BankTeller::serveClient, &teller, std::ref(prioritaryQueue), std::ref(queueMutex)));
                else
                {
                    // Si la cola prioritaria está vacía, asigna un cliente de la cola normal
                    threads.emplace_back(std::thread(&BankTeller::serveClient, &teller, std::ref(normalQueue), std::ref(queueMutex)));
                }
            }
            
            // Espera a que todos los hilos terminen de atender a sus respectivos clientes
            for (auto &thread : threads)
            {
                thread.join(); // Unir todos los hilos
            }
            threads.clear(); // Limpia el vector de hilos para el siguiente ciclo
        }

        std::cout << "Todos los clientes han sido atendidos." << std::endl;
    };
};
