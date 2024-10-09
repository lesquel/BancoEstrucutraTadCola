#pragma once

#include <iostream>
#include <mutex>
#include "thread"
#include "chrono"

#include "bankQueue.hpp"
#include "person.hpp"
#include "typeOperation.hpp"

class BankTeller
{
private:
    std::string banTellerName;
    typeOperation operation;
    int serviceTime = 0;

public:
    BankTeller(std::string banTellerName, typeOperation operation)
    {
        this->banTellerName = banTellerName;
        this->operation = operation;
    }

    std::string getnumber() const { return banTellerName; }
    int getServiceTime() const { return operation; }

    void serveClient(BankQueue &cola, std::mutex &queueMutex)
    {

        std::string clientName;
        {
            std::lock_guard<std::mutex> lock(queueMutex);

            if (cola.isEmpty())
            {
                return;
            }

            Person client = cola.dequeue();
            clientName = client.getName();
            if (client.isElder())
                std::cout << "\nCliente " << clientName << "(Mayor) atendido en la caja " << banTellerName << std::endl;

            else
            {
                std::cout << "\nCliente " << clientName << " atendido en la caja " << banTellerName << std::endl;
            }
            std::cout << "Tiempo de espera: " << serviceTime << ", tiempo de transaccion: " << getServiceTime() << std::endl;
        }
        serviceTime += getServiceTime();

        std::cout << "__________________________________________" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(operation));
    }
};