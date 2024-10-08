#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "person.hpp"
using namespace std;
using namespace std::this_thread;

class Cashier
{
private:
    Person persona;
    int numero;
    bool ocupado;
    int tiempoDeEspera;
    bool prioridad;
    mutex mtx; // Mutex para controlar el acceso concurrente

public:
    Cashier(int n, int t, bool pr)
    {
        numero = n;
        ocupado = false;
        tiempoDeEspera = t;
        prioridad = pr;
    }

    Person getPersona() const { return persona; }
    int getNumero() const { return numero; }
    bool getOcupado() const { return ocupado; }
    int getTiempoDeEspera() const { return tiempoDeEspera; }
    bool getPrioridad() const { return prioridad; }
    void setOcupado(bool estado) { ocupado = estado; }

    void Trabajo(Person p)
    {
        // Bloqueo del mutex para acceso seguro
        lock_guard<mutex> lock(mtx);
        setOcupado(true);
        cout << "Se esta atendiendo a " << p.getName() << " en la caja " << numero << endl;
        sleep_for(chrono::seconds(tiempoDeEspera));
        cout << "Se ha terminado el trabajo en la caja " << numero << endl;
        setOcupado(false);
    }

    // Método para atender a un cliente en un hilo separado
    void atenderCliente(Person p)
    {
        thread t(&Cashier::Trabajo, this, p);
        t.detach(); // Permite que el hilo se ejecute independientemente
    }
};
