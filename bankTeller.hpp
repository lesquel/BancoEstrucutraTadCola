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
    std::string banTellerName;      // Nombre del cajero
    typeOperation operation;        // Tipo de operación que realiza el cajero (depósito, retiro o ambos)
    int serviceTime = 0;            // Tiempo total de servicio (se incrementa con cada transacción)

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

    /**
     * Devuelve el nombre del cajero.
     * 
     * @return std::string Nombre del cajero.
     */
    std::string getnumber() const { return banTellerName; }

    /**
     * Devuelve el tiempo de servicio asociado al tipo de operación.
     * 
     * @return int Tiempo de servicio en segundos.
     */
    int getServiceTime() const { return operation; }

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
            if (client.isElder())
            {
                std::cout << "\nCliente " << clientName << " (Mayor) atendido en la caja " << banTellerName << std::endl;
            }
            else
            {
                std::cout << "\nCliente " << clientName << " atendido en la caja " << banTellerName << std::endl;
            }

            // Mostrar tiempos de espera y transacción
            std::cout << "Tiempo de espera: " << serviceTime << ", tiempo de transacción: " << getServiceTime() << std::endl;
        }

        // Actualizar el tiempo total de servicio del cajero
        serviceTime += getServiceTime();

        // Separador visual en la consola
        std::cout << "__________________________________________" << std::endl;

        // Simular el tiempo de operación (depósito o retiro) del cajero
        std::this_thread::sleep_for(std::chrono::seconds(operation));
    }
};
