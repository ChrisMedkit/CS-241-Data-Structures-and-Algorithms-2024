#include "transportation.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
    try {
        //makes list of features for the cars
        NodeList<string> features1;
        features1.insertBack("AC");
        features1.insertBack("DVD");
        features1.insertBack("GPS");
        features1.insertBack("Sunroof");

        NodeList<string> features2;
        features2.insertBack("Bluetooth");
        features2.insertBack("Navigation");
        features2.insertBack("Leather Seats");

        //vehicle instances
        Vehicle v1(1234, "Honda", "Pilot", 6, true, 4, features1);
        Vehicle v2(5678, "Toyota", "Camry", 5, true, 3, features2);
        Vehicle v3(9101, "Ford", "Mustang", 2, false, 2, features1);

        //make an inventory and add cars
        Inventory inv;
        inv.push_Back(v1);
        inv.push_Back(v2);
        inv.push_Back(v3);

        //print all cars
        cout << "All Vehicles in Inventory:" << endl;
        inv.printList();
        cout << endl;

        //print reserved cars
        cout << "Reserved Vehicles:" << endl;
        inv.printReservedList();
        cout << endl;

        //print available cars
        cout << "Available Vehicles:" << endl;
        inv.printAvailableList();
        cout << endl;

        //attempt to reserving a car
        cout << "Attempting to reserve vehicle with ID 1234..." << endl;
        try {
            inv.reserveVehicle(1234);
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        cout << endl;

        //print available cars after attempt to reserve
        cout << "Available Vehicles After Reservation Attempt:" << endl;
        inv.printAvailableList();
        cout << endl;

        //try to returning a car
        cout << "Attempting to return vehicle with ID 1234..." << endl;
        try {
            inv.returnVehicle(1234);
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        cout << endl;

        //print available cars after try
        cout << "Available Vehicles After Return Attempt:" << endl;
        inv.printAvailableList();
        cout << endl;

        //save car inventiry to file
        cout << "Saving inventory to file 'inventory.txt'..." << endl;
        try {
            inv.saveToFile("inventory.txt");
            cout << "Inventory saved successfully." << endl;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

        //check if a car with 5 seats exists
        cout << "Searching for a vehicle with 5 seats..." << endl;
        if (inv.found(5)) {
            cout << "Vehicle with 5 seats found." << endl;
        }
        else {
            cout << "Vehicle with 5 seats not found." << endl;
        }

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
