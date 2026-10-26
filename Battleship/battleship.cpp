#include "battleship.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// Location Class Implementations

Location::Location() {
    coordinates = new int[2] {-1, -1};
}

Location::Location(int x, int y) {
    coordinates = new int[2] {x, y};
}

void Location::pick() {
    coordinates[0] = rand() % FIELD_SIZE + 1;
    coordinates[1] = rand() % FIELD_SIZE + 1;
}

void Location::fire() {
    cout << "Enter coordinates (x y): ";
    cin >> coordinates[0] >> coordinates[1];
}

void Location::print() const {
    cout << "[" << coordinates[0] << "," << coordinates[1] << "]" << endl;
}

bool compare(const Location& loc1, const Location& loc2) {
    return loc1.coordinates[0] == loc2.coordinates[0] && loc1.coordinates[1] == loc2.coordinates[1];
}

Location::Location(const Location& other) {
    coordinates = new int[2] {other.coordinates[0], other.coordinates[1]};
}

Location& Location::operator=(const Location& other) {
    if (this == &other) return *this;
    coordinates[0] = other.coordinates[0];
    coordinates[1] = other.coordinates[1];
    return *this;
}

Location::~Location() {
    delete[] coordinates;
}

// Ship Class Implementations

Ship::Ship() : sunk(false) {}

bool Ship::match(const Location& loc) const {
    return this->loc == loc;
}

void Ship::sink() {
    sunk = true;
}

void Ship::setLocation(const Location& loc) {
    this->loc = loc;
}

void Ship::printShip() const {
    loc.print();
    cout << "->" << (sunk ? "sunk" : "up") << endl;
}

ostream& operator<<(ostream& os, const Ship& sh) {
    sh.printShip();
    return os;
}

// Fleet Class Implementations

void Fleet::deployFleet() {
    for (int i = 0; i < FLEET_SIZE; ++i) {
        Location loc;
        do {
            loc.pick();
        } while (check(loc) != -1);
        ships[i].setLocation(loc);
    }
}

bool Fleet::operational() const {
    for (int i = 0; i < FLEET_SIZE; ++i) {
        if (!ships[i].isSunk()) {
            return true;
        }
    }
    return false;
}

int Fleet::isHitNSink(const Location& loc) {
    int index = check(loc);
    if (index != -1) {
        if (!ships[index].isSunk()) {
            ships[index].sink();
            return 1;
        }
        else {
            return 2; // Already sunk
        }
    }
    return 0;
}

void Fleet::printFleet() const {
    for (int i = 0; i < FLEET_SIZE; ++i) {
        cout << ships[i] << endl;
    }
}

Ship* Fleet::getShipList() {
    return ships;
}

int Fleet::getFleetSize() {
    return FLEET_SIZE;
}

int Fleet::check(const Location& loc) const {
    for (int i = 0; i < FLEET_SIZE; ++i) {
        if (ships[i].match(loc)) {
            return i;
        }
    }
    return -1;
}
