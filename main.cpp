#include <iostream>

using namespace std;

#include "bank.hpp"
#include "person.hpp"

//Simular horas de ejecucion -- Bryan Steven Menoscal Santana
void excecuteFunction(int num_hours, Bank &bank)
{
    for (int i = 0; i < num_hours; i++)
    {
        std::vector<Person> clients = generateClients(20); // esta funcion esta en person.hpp

        for (auto &client : clients)
        {
            bank.addClient(client);
            client.print_client();
        }
        bank.startService();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    Bank bank("Banco Pichincha");

    excecuteFunction(6,bank);

    return 0;
}
