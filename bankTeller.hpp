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
    std::string banTellerName; // Nombre del cajero
    typeOperation operation;   // Tipo de operación que realiza el cajero (depósito, retiro o ambos)
    int serviceTime = 0;       // Tiempo total de servicio (se incrementa con cada transacción)
    int numBankTellersReasignation;        // Mutex para controlar el acceso concurrente a las colas


public:
    /**
     * Constructor de la clase BankTeller.
     *
     * @param banTellerName Nombre del cajero.
     * @param operation Tipo de operación que realiza el cajero (definido por typeOperation).
     *
     * Este constructor inicializa un cajero con un nombre y el tipo de operación que maneja.
     */
    BankTeller(std::string banTellerName, typeOperation operation)
    {
        this->banTellerName = banTellerName;
        this->operation = operation;
    }

    std::string getName() const { return banTellerName; }

    int getServiceTime() const { return operation; }


    char typeOperationFunc() {
        char s = 'B';  // Cambiamos por comillas simples para un `char`
        if (operation == typeOperation::DEPOSIT) {
            s = 'D';
        } else if (operation == typeOperation::WITHDRAWAL) {
            s = 'W';
        }
        return s;
    }

    // convierte la caja en en otro tipo de operacion
    void ConvertBankTellerType(typeOperation op){
        numBankTellersReasignation++;
        operation = op;
    }

    // Obtener el numero de veces que se cambio de caja - Bryan Steven Menoscal Santana

    int getNumBankTellerreasgnation(){
        return numBankTellersReasignation;
    }

    /**
     * Sirve a un cliente de la cola.
     *
     * @param cola Cola de clientes que se procesará (BankQueue).
     * @param queueMutex Mutex para garantizar acceso seguro a la cola.
     *
     * Este método intenta atender a un cliente de la cola pasada como referencia.
     * Si la cola no está vacía, extrae un cliente, lo atiende y muestra el tiempo de servicio.
     * Si el cliente es mayor, se indica que ha sido atendido prioritariamente.
     *
     * Luego, se simula el tiempo de transacción con `std::this_thread::sleep_for()`, basado
     * en el tipo de operación del cajero.
     */
    void serveClient(BankQueue &cola, std::mutex &queueMutex)
    {
        std::string clientName; // Nombre del cliente que será atendido

        {
            // Bloqueo del mutex mientras se accede a la cola
            std::lock_guard<std::mutex> lock(queueMutex);

            // Si la cola está vacía, no hay nada que hacer
            if (cola.isEmpty())
            {
                return;
            }

            // Dequeue (extraer) al cliente de la cola
            Person client = cola.dequeue();
            clientName = client.getName();

            // Verifica si el cliente es mayor para dar prioridad
            if (client.isElder()) {
                std::cout << "\n******************" << std::endl;
                std::cout << "* " << banTellerName << " " << typeOperationFunc() 
                        << " | " << clientName << " *" << std::endl;
                std::cout << "******************" << std::endl;
            } else {
                std::cout << "\n******************" << std::endl;
                std::cout << "* " << banTellerName << " " << typeOperationFunc() 
                        << " | " << clientName << " *" << std::endl;
                std::cout << "******************" << std::endl;
            }


            // Mostrar tiempos de espera y transacción

            std::cout << "Tiempo de espera: " << serviceTime << ", tiempo de transaccion: " << getServiceTime() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(operation));
            serviceTime += getServiceTime();
        }

        // Actualizar el tiempo total de servicio del cajero

        // Separador visual en la consola
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Ajustar según sea necesario
    }



    
};
