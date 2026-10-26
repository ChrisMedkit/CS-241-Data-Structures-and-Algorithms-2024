#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

// Coordinates (location) of the ship and shots
class Location {
public:
    Location();
    Location(int, int);
    void pick();
    void fire();
    void print() const;
    int getCoordX() const { return coordinates[0]; }
    int getCoordY() const { return coordinates[1]; }
    friend bool compare(const Location&, const Location&);
    Location(const Location&);
    Location& operator=(const Location&);
    ~Location();
    bool operator==(Location rhs) const {
        return (coordinates[0] == rhs.coordinates[0] && coordinates[1] == rhs.coordinates[1]);
    }
    static const int FIELD_SIZE = 6;
private:
    int* coordinates;
};

class Ship {
public:
    Ship();
    bool match(const Location&) const;
    bool isSunk() const { return sunk; }
    void sink();
    void setLocation(const Location&);
    void printShip() const;
    Location getLocation() { return loc; }
    friend ostream& operator<<(ostream& os, const Ship& sh);
private:
    Location loc;
    bool sunk;
};

class Fleet {
public:
    void deployFleet();
    bool operational() const;
    int isHitNSink(const Location&);
    void printFleet() const;
    Ship* getShipList();
    int getFleetSize();
private:
    static const int FLEET_SIZE = 6;
    int check(const Location&) const;
    Ship ships[FLEET_SIZE];
};

#endif /* BATTLESHIP_H_ */
