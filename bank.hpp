#pragma once

#include "queue.hpp"
#include "cashier.hpp"

class Bank{
    private:
        Queue queue;
        Cashier *cashiers;
        int numCashiers;
        
    public:
        Bank(int numCashiers, int queueCapacity){
            this->numCashiers = numCashiers;
            queue = Queue(queueCapacity);
            cashiers = new Cashier[numCashiers];
        }

        void addClient(Person client){
            queue.enqueue(client);
        }

        void start(){
            std::mutex queueMutex;
            std::thread cashierThreads[numCashiers];
            for(int i = 0; i < numCashiers; i++){
                cashierThreads[i] = std::thread(&Cashier::serveClient, &cashiers[i], std::ref(queue), std::ref(queueMutex));
            }

            for(int i = 0; i < numCashiers; i++){
                cashierThreads[i].join();
            }
        }
};