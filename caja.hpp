#pragma once
#include <iostream>
#include <string>
#include <thread>
#include "person.hpp"
using namespace std;
using namespace std::this_thread;


class Caja
{
private:
    Persona persona;
    int numero;
    bool ocupado;
    int tiempoDeEspera;
    bool prioridad;

public:
    Caja(Persona p, int n, int t, bool pr)
    {
        persona = p;
        numero = n;
        ocupado = false;
        tiempoDeEspera = t;
        prioridad = pr;
    }

    Persona getPersona() const { return persona; }
    int getNumero() const { return numero; }
    bool getOcupado() const { return ocupado; }
    int getTiempoDeEspera() const { return tiempoDeEspera; }
    bool getPrioridad() const { return prioridad; }
    void Tabajo(Persona p)
    {
        ocupado = true;
        cout << "Se esta atendiendo a " << p.getNombre() << " en la caja " << numero << endl;
        sleep_for(seconds(tiempoDeEspera));
        ocupado = false;
        cout << "Se ha terminado el trabajo en la caja " << numero << endl;
    }
};
