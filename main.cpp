#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

class Persona
{
private:
    string nombre;
    int edad;
    string direccion;
    bool prioridad;

public:
    Persona(string n = "", int e = 0, string d = "") : nombre(n), edad(e), direccion(d) {}

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    string getDireccion() const { return direccion; }
};
class Persona; // Forward declaration

class Caja
{
private:
    Persona persona;
    int numero;
    bool ocupado;
    int tiempoDeEspera;
    bool prioridad;

public:
    Caja(Persona p, int n, bool o, int t, bool pr)
    {
        persona = p;
        numero = n;
        ocupado = o;
        tiempoDeEspera = t;
        prioridad = pr;
    }

    Persona getPersona() const { return persona; }
    int getNumero() const { return numero; }
    bool getOcupado() const { return ocupado; }
    int getTiempoDeEspera() const { return tiempoDeEspera; }
    bool getPrioridad() const { return prioridad; }
};

class Cola
{
private:
    Persona *arreglo;
    int first, last;
    int capacity;

public:
    Cola(int cap)
    {
        capacity = cap;
        arreglo = new Persona[capacity];
        first = -1;
        last = -1;
    }

    bool isEmpty() const
    {
        return (first == -1);
    }

    bool isFull() const
    {
        return (last == capacity - 1);
    }

    void enqueue(Persona x)
    {
        if (isFull())
        {
            cout << "Cola llena" << endl;
            return;
        }
        if (first == -1)
        {
            first = 0;
        }
        last++;
        arreglo[last] = x;
    }

    Persona dequeue()
    {
        if (isEmpty())
        {
            cout << "Cola vacia" << endl;
            return Persona(); // Retornar un objeto por defecto
        }
        Persona x = arreglo[first];
        first++;
        if (first > last)
        {
            first = -1;
            last = -1;
        }
        return x;
    }

    void front() const
    {
        if (isEmpty())
        {
            cout << "Cola vacia" << endl;
            return;
        }
        cout << "Primer trabajo en la cola: " << arreglo[first].getNombre() << ", Tamaño: " << arreglo[first].getEdad() << endl;
    }

    int size() const
    {
        if (first == -1)
        {
            return 0;
        }
        return last - first + 1;
    }
};

int main()
{
    return 0;
}
