#pragma once

#include <iostream>
#include <mutex>
#include "thread"
#include "chrono"

#include "queue.hpp"

class Cashier
{
private:
    int cashierId;
    bool occupied;
    int serviceTime;
    bool priority;
    std::string operation;

public:


    Cashier(int cashierId=0, int waitingTime=0, bool priority=false)
    {
        this->cashierId = cashierId;
        this->occupied = false;
        this->serviceTime = waitingTime;
        this->priority = priority;
    }

    int getnumber() const { return cashierId; }
    bool isOccupied() const { return occupied; }
    int getServiceTime() const { return serviceTime; }
    bool getPriority() const { return priority; }


    void serveClient(Queue &cola, std::mutex &queueMutex)
    {
        std::string clientName;
        {
            std::lock_guard<std::mutex> lock(queueMutex);

            if (cola.isEmpty())
            {
                return;
            }

            clientName = cola.dequeue().getName();
            occupied = true;
            std::cout << "Atendiendo al cliente " << clientName << " en la caja " << cashierId << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(serviceTime));

        std::cout << "--- El cliente " << clientName << " ha sido atendido en la caja " << cashierId << std::endl;
        occupied = false;
    }
};