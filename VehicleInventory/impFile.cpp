#include "transportation.h"

//vehicle 

Vehicle::Vehicle() : vehicleID(0), make(""), model(""), seats(0), available(true), extarFeatures(0) {}

Vehicle::Vehicle(int id, string mk, string mdl, int s, bool avail, int extFeat, NodeList<string> features)
    : vehicleID(id), make(mk), model(mdl), seats(s), available(avail), extarFeatures(extFeat), otherFeaturesList(features) {}

Vehicle::~Vehicle() {}

Vehicle::Vehicle(const Vehicle& rhs) : vehicleID(rhs.vehicleID), make(rhs.make), model(rhs.model),
seats(rhs.seats), available(rhs.available), extarFeatures(rhs.extarFeatures), otherFeaturesList(rhs.otherFeaturesList) {}

Vehicle& Vehicle::operator=(const Vehicle& rhs) {
    if (this != &rhs) {
        vehicleID = rhs.vehicleID;
        make = rhs.make;
        model = rhs.model;
        seats = rhs.seats;
        available = rhs.available;
        extarFeatures = rhs.extarFeatures;
        otherFeaturesList = rhs.otherFeaturesList;
    }
    return *this;
}

bool Vehicle::operator>(const Vehicle& rhs) {
    return seats > rhs.seats;
}

bool Vehicle::operator<(const Vehicle& rhs) {
    return seats < rhs.seats;
}

bool Vehicle::operator==(const Vehicle& rhs) {
    return seats == rhs.seats;
}

bool Vehicle::operator<=(const Vehicle& rhs) {
    return seats <= rhs.seats;
}

bool Vehicle::operator>=(const Vehicle& rhs) {
    return seats >= rhs.seats;
}

bool Vehicle::operator!=(const Vehicle& rhs) {
    return seats != rhs.seats;
}

ostream& operator<<(ostream& out, const Vehicle& v) {
    out << "ID: " << v.vehicleID << ", Make: " << v.make << ", Model: " << v.model
        << ", Seats: " << v.seats << ", Available: " << (v.available ? "Yes" : "No")
        << ", Extra Features: " << v.extarFeatures << "\nFeatures List: ";

    NodeList<string> features = v.getFeaturesList();
    for (auto it = features.begin(); it != features.end(); ++it) {
        out << *it << " ";
    }
    out << endl;
    return out;
}

ofstream& operator<<(ofstream& out, const Vehicle& v) {
    out << "ID: " << v.vehicleID << ", Make: " << v.make << ", Model: " << v.model
        << ", Seats: " << v.seats << ", Available: " << (v.available ? "Yes" : "No")
        << ", Extra Features: " << v.extarFeatures << "\nFeatures List: ";

    NodeList<string> features = v.getFeaturesList();
    for (auto it = features.begin(); it != features.end(); ++it) {
        out << *it << " ";
    }
    out << endl;
    return out;
}

//inventory

Inventory::Inventory() : capacity(0), registredVehiclesNo(0), v_List() {}

Inventory::Inventory(int cap) : capacity(cap), registredVehiclesNo(0), v_List() {}

Inventory::~Inventory() {}

Inventory::Inventory(const Inventory& rhs) : capacity(rhs.capacity), registredVehiclesNo(rhs.registredVehiclesNo), v_List(rhs.v_List) {}

Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        capacity = rhs.capacity;
        registredVehiclesNo = rhs.registredVehiclesNo;
        v_List = rhs.v_List;
    }
    return *this;
}

bool Inventory::push_Back(Vehicle v) {
    v_List.insertBack(v);
    registredVehiclesNo++;
    return true;
}

void Inventory::sortList() {
    //algorithm sorting
}

void Inventory::printList() {
    printListHelper(v_List.begin());
}

void Inventory::printListHelper(NodeList<Vehicle>::Iterator it) {
    if (it == v_List.end()) return;
    cout << *it << endl;
    printListHelper(++it);
}

void Inventory::printReservedList() {
    printReservedListHelper(v_List.begin());
}

void Inventory::printReservedListHelper(NodeList<Vehicle>::Iterator it) {
    if (it == v_List.end()) return;
    if (!(*it).status()) cout << *it << endl;
    printReservedListHelper(++it);
}

void Inventory::printAvailableList() {
    printAvailableListHelper(v_List.begin());
}

void Inventory::printAvailableListHelper(NodeList<Vehicle>::Iterator it) {
    if (it == v_List.end()) return;
    if ((*it).status()) cout << *it << endl;
    printAvailableListHelper(++it);
}

bool Inventory::found(int seatsNo) {
    return foundHelper(v_List.begin(), seatsNo);
}

bool Inventory::foundHelper(NodeList<Vehicle>::Iterator it, int seatsNo) {
    if (it == v_List.end()) return false;
    if ((*it).getSeats() == seatsNo) return true;
    return foundHelper(++it, seatsNo);
}

bool Inventory::reserveVehicle(int id) {
    for (auto it = v_List.begin(); it != v_List.end(); ++it) {
        if ((*it).getID() == id) {
            if (!(*it).status()) {
                throw logic_error("Vehicle is already reserved.");
            }
            (*it).reserve();
            return true;
        }
    }
    throw invalid_argument("Invalid vehicle ID.");
}

bool Inventory::returnVehicle(int id) {
    for (auto it = v_List.begin(); it != v_List.end(); ++it) {
        if ((*it).getID() == id) {
            if ((*it).status()) {
                throw logic_error("Vehicle is not reserved.");
            }
            (*it).unReserve();
            return true;
        }
    }
    throw invalid_argument("Invalid vehicle ID.");
}

int Inventory::checkID(int id) {
    //logic to check ids
    return -1;
}

bool Inventory::saveToFile(string fileName) {
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        throw runtime_error("File not found or cannot be opened for writing.");
    }

    for (auto it = v_List.begin(); it != v_List.end(); ++it) {
        outFile << *it << endl;
    }
    outFile.close();
    return true;
}

ofstream& operator<<(ofstream& out, const Inventory& inv) {
    for (auto it = inv.v_List.begin(); it != inv.v_List.end(); ++it) {
        out << *it << endl;
    }
    return out;
}
