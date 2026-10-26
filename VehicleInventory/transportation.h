#pragma once
#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include <string>
#include <iostream>
#include <fstream>
#include "NodeList.h"

using namespace std;

class Vehicle {
public:
    Vehicle();
    Vehicle(int, string, string, int, bool, int, NodeList<string>);
    void reserve() { available = 0; }
    void unReserve() { available = 1; }
    bool status() const { return available; }
    int getID() const { return vehicleID; }
    string getmake() const { return make; }
    string getmodel() const { return model; }
    int getSeats() const { return seats; }
    int getextarFeatures() const { return extarFeatures; }
    NodeList<string> getFeaturesList() const { return otherFeaturesList; }
    ~Vehicle(); 
    Vehicle(const Vehicle&);  
    Vehicle& operator=(const Vehicle& rhs); 

    // operators overloading 
    bool operator>(const Vehicle&);
    bool operator<(const Vehicle&);
    bool operator==(const Vehicle&);
    bool operator<=(const Vehicle&);
    bool operator>=(const Vehicle&);
    bool operator!=(const Vehicle&);

    friend ostream& operator<<(ostream& out, const Vehicle&);
    friend ofstream& operator<<(ofstream& out, const Vehicle&);

private:
    int vehicleID;
    string make;
    string model;
    int seats;
    bool available;
    int extarFeatures;
    NodeList<string> otherFeaturesList;
};

class Inventory {
public:
    Inventory();
    Inventory(int);

    Inventory(const Inventory&);  
    Inventory& operator=(const Inventory&); 
    ~Inventory();

    bool push_Back(Vehicle);
    void sortList();
    void printList();
    void printReservedList();
    void printAvailableList();
    bool found(int);
    bool reserveVehicle(int);
    bool returnVehicle(int);
    int checkID(int);
    int size() { return registredVehiclesNo; }
    bool saveToFile(string fileName);

    friend ofstream& operator<<(ofstream&, const Inventory&);

private:
    int capacity;
    int registredVehiclesNo;
    NodeList<Vehicle> v_List; 

    void printListHelper(NodeList<Vehicle>::Iterator it);
    void printReservedListHelper(NodeList<Vehicle>::Iterator it);
    void printAvailableListHelper(NodeList<Vehicle>::Iterator it);
    bool foundHelper(NodeList<Vehicle>::Iterator it, int seatsNo);
};

#endif
