#include <iostream>

using namespace std;

#include "bank.hpp"
#include "person.hpp"

void showMenu() {
    cout << "====================================" << endl;
    cout << "           Banco Pichincha          " << endl;
    cout << "====================================" << endl;
    cout << "1. Add Client" << endl;
    cout << "2. Start Service" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option: ";
}

int main() {
    // Bank bank("Banco Pichincha");
    // int option;

    // while (true) {
    //     showMenu();
    //     cin >> option;

    //     if (option == 1) {
    //         string name;
    //         int operation;
    //         bool isElder;

    //         // Get client information
    //         cout << "Enter client name: ";
    //         cin >> name;

    //         cout << "Enter operation (0 for DEPOSIT, 1 for WITHDRAWAL): ";
    //         cin >> operation;

    //         cout << "Is the client elder? (0 for No, 1 for Yes): ";
    //         cin >> isElder;

    //         // Create the client and add to the bank
    //         Person newClient(name, static_cast<typeOperation>(operation), isElder);
    //         bank.addClient(newClient);

    //         cout << "Client " << name << " added successfully!" << endl;

    //     } else if (option == 2) {
    //         bank.startService();
    //     } else if (option == 3) {
    //         cout << "Exiting the application. Thank you!" << endl;
    //         break;
    //     } else {
    //         cout << "Invalid option. Please try again." << endl;
    //     }
    // }

    Bank bank("Banco Pichincha");
    Person person1("Juan", DEPOSIT, false);
    Person person2("Maria", WITHDRAWAL, true);
    Person person3("Pedro", WITHDRAWAL, true);
    Person person4("Ana", DEPOSIT, true);
    Person person5("Luisa", DEPOSIT, false);
    Person person6("Robert", DEPOSIT, true);
    Person person7("Albert", DEPOSIT, true);
    bank.addClient(person1);
    bank.addClient(person2);
    bank.addClient(person3);
    bank.addClient(person4);
    bank.addClient(person5);
    bank.addClient(person6);
    bank.addClient(person7);
    bank.startService();

    return 0;
}




