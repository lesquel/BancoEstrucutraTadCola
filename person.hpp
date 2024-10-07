#pragma once

#include <iostream>
#include <string>
using namespace std;


class Persona
{
private:
    string nombre;
    int edad;
    string direccion;
    bool prioridad;
    bool atendido;
public:
    Persona(string n = "", int e = 0, string d = "", bool p = false)
    {
        nombre = n;
        edad = e;
        direccion = d;
        prioridad = p;
        atendido = false;
    }

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    string getDireccion() const { return direccion; }
    bool getPrioridad() const { return prioridad; }
    bool getAtendido() const { return atendido; }
    void setAtendido(bool a) { atendido = a; }
};
