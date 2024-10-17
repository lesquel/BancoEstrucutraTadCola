#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib> // Para system()
#include <mutex>
#include <chrono>

#include "bankQueue.hpp"
#include "bankTeller.hpp"
#include "person.hpp"
#pragma once

class Bank
{
private:
    std::string bankName;                // Nombre del banco
    BankQueue normalQueue;               // Cola de clientes regulares
    BankQueue prioritaryQueue;           // Cola de clientes prioritarios (por ejemplo, ancianos)
    BankQueue retiroQueue;               // Cola de clientes prioritarios (por ejemplo, ancianos)
    BankQueue depositoQueue;             // Cola de clientes prioritarios (por ejemplo, ancianos)
    std::vector<BankTeller> bankTellers; // Vector que almacena los cajeros del banco
    std::mutex queueMutex;
    int maxQueueLengthAlert = 20;        // Alerta si la longitud de la cola excede este valor
    int maxWaitTimeAlert = 10;           // Alert if average wait time exceeds 10 minutes
    bool stopReporting = false;          // Bandera para detener el hilo de informes
    int QUEUECAPACITY = 40; // Capacidad máxima de las colas de clientes

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
        this->retiroQueue = BankQueue(QUEUECAPACITY);               // Cola de clientes prioritarios
        this->depositoQueue = BankQueue(QUEUECAPACITY);           
        bankTellers.emplace_back(BankTeller("Deposito", DEPOSIT));  // Cajero especializado en depósitos
        bankTellers.emplace_back(BankTeller("Retiro", WITHDRAWAL)); // Cajero especializado en retiros
        bankTellers.emplace_back(BankTeller("Especial", BOTH));     // Cajero que maneja tanto depósitos como retiros
        // bankTellers.emplace_back(BankTeller("Especial2", BOTH));     // Cajero que maneja tanto depósitos como retiros
    }

    // agrege las otras colas
    void addClient(Person client)
    {
        if (client.isElder())
        {
            prioritaryQueue.enqueue(client);
        }
        // else if (client.getOperation() == DEPOSIT)
        // {
        //     depositoQueue.enqueue(client);
        // }
        // else if (client.getOperation() == WITHDRAWAL)
        // {
        //     retiroQueue.enqueue(client);
        // }
        else
        {
            normalQueue.enqueue(client);
        }
    }

    void printName(BankQueue &tempQueue)
    {
        while (!tempQueue.isEmpty())
        {
            Person person = tempQueue.dequeue(); // Extraer el elemento
            std::cout << person.getName() << " | ";
        }
    }

    void PrintPersons()
    {
        std::cout << "Priority Queue:" << std::endl;
        // Crear una copia para no modificar la cola original
        BankQueue tempQueue = prioritaryQueue;

        printName(tempQueue);
        std::cout << "-----------------------------------------------" << std::endl;

        std::cout << "\n Normal Queue:" << std::endl;
        tempQueue = normalQueue;

        std::cout << "-----------------------------------------------" << std::endl;
        printName(tempQueue);
    }

    // printQueueStats es un método privado que imprime las estadísticas de una cola
    void printQueueStats(BankQueue &queue, const std::string &queueName)
    {
        int queueLength = queue.sizeCircular();
        std::cout << queueName << " - Size: " << queueLength << std::endl;

        if (queueLength > maxQueueLengthAlert)
        {
            std::cout << "⚠️ ALERT: " << queueName << " length exceeded " << maxQueueLengthAlert << "!" << std::endl;
        }
    }

    double calculateAverageWaitTime(BankQueue &queue)
    {
        std::lock_guard<std::mutex> lock(queueMutex);

        if (queue.isEmpty())
            return 0.0;

        auto now = std::chrono::steady_clock::now();
        double totalWaitTime = 0;

        while (!queue.isEmpty())
        {
            totalWaitTime += queue.dequeue().getOperation();
        }

        return totalWaitTime / queue.sizeCircular();
    }

    void reportStatistics()
    {
        while (!stopReporting)
        {
            std::this_thread::sleep_for(std::chrono::seconds(10)); // Report every 10 seconds

            std::cout << "\n===== Real-Time Statistics =====\n";

            printQueueStats(prioritaryQueue, "Prioritary Queue");
            printQueueStats(normalQueue, "Normal Queue");

            double prioritaryAvgWait = calculateAverageWaitTime(prioritaryQueue);
            double normalAvgWait = calculateAverageWaitTime(normalQueue);

            std::cout << "Average Wait Time (Priority): " << prioritaryAvgWait << " minutes" << std::endl;
            std::cout << "Average Wait Time (Normal): " << normalAvgWait << " minutes" << std::endl;

            if (prioritaryAvgWait > maxWaitTimeAlert)
            {
                std::cout << "⚠️ ALERT: Priority queue wait time exceeded " << maxWaitTimeAlert << " minutes!" << std::endl;
            }
            if (normalAvgWait > maxWaitTimeAlert)
            {
                std::cout << "⚠️ ALERT: Normal queue wait time exceeded " << maxWaitTimeAlert << " minutes!" << std::endl;
            }
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
            else if (!retiroQueue.isEmpty())
            {
                if (retiroQueue.sizeCircular() < QUEUECAPACITY / 2)
                {
                    bankTellers[2].ConvertBankTellerType(DEPOSIT);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                threads.emplace_back(std::thread([this, &teller = bankTellers[2]]
                                                 { teller.serveClient(retiroQueue, queueMutex); }));
            }
            else if (!depositoQueue.isEmpty())
            {
                if (retiroQueue.sizeCircular() < QUEUECAPACITY / 2)
                {
                    bankTellers[2].ConvertBankTellerType(WITHDRAWAL);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                threads.emplace_back(std::thread([this, &teller = bankTellers[2]]
                                                 { teller.serveClient(depositoQueue, queueMutex); }));
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

            // system("cls"); // Limpia la consola
        }

        std::cout << "Todos los clientes han sido atendidos." << std::endl;
    }
};
