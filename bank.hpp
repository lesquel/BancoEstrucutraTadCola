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
    BankQueue normalQueue;               // Cola de clientes
    BankQueue prioritaryQueue;           // Cola de clientes prioritarios
    std::vector<BankTeller> bankTellers; // Vector para almacenar cajeros
    std::mutex queueMutex;               // Mutex para controlar el acceso a las colas
    int QUEUECAPACITY = 20;

public:
    Bank(std::string bankName)
    {
        this->bankName = bankName;                                  // Nombre del banco
        this->normalQueue = BankQueue(QUEUECAPACITY);               // Cola de clientes
        this->prioritaryQueue = BankQueue(QUEUECAPACITY);           // Cola de clientes prioritarios
        bankTellers.emplace_back(BankTeller("Deposito", DEPOSIT));  // Cajero de de deposito
        bankTellers.emplace_back(BankTeller("Retiro", WITHDRAWAL)); // Cajero de retiro
        bankTellers.emplace_back(BankTeller("Especial", BOTH));     // Cajero de deposito y retiro
        // bankTellers.emplace_back(BankTeller("Especial222", DEPOSIT));     // Cajero de deposito y retiro
    }

    BankQueue getNormalQueue()
    {
        return normalQueue;
    }
    BankQueue getPrioritaryQueue()
    {
        return prioritaryQueue;
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

    void startService()
    {
        std::vector<std::thread> threads;

        while (!normalQueue.isEmpty() || !prioritaryQueue.isEmpty())
        {
            for (auto &teller : bankTellers)
            {
                if (!prioritaryQueue.isEmpty())
                    threads.emplace_back(std::thread(&BankTeller::serveClient, &teller, std::ref(prioritaryQueue), std::ref(queueMutex)));
                else
                {
                    threads.emplace_back(std::thread(&BankTeller::serveClient, &teller, std::ref(normalQueue), std::ref(queueMutex)));
                }
            }
            for (auto &thread : threads)
            {
                thread.join();
            }
            threads.clear();
        }
        std::cout << "Todos los clientes han sido atendidos." << std::endl;
    };
};
