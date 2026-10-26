#include "battleship.h"
#include <iostream>

using namespace std;

int main() {
    srand(time(nullptr)); // Seed the random number generator

    Fleet fleet; // Declare an object of class fleet
    fleet.deployFleet(); // Deploy the fleet of ships

    char printFleet;
    cout << "Would you like to print the ships' positions and statuses? (y/n): ";
    cin >> printFleet;
    if (printFleet == 'y' || printFleet == 'Y') {
        fleet.printFleet(); // Print the fleet positions and statuses
    }

    while (fleet.operational()) { // Loop while the fleet is operational
        Location loc; // Declare a location object for the user's shot
        loc.fire(); // Prompt the user to enter coordinates for the shot

        int result = fleet.isHitNSink(loc); // Check if the shot hits and sinks a ship
        switch (result) {
        case 0:
            cout << "Miss!" << endl;
            break;
        case 1:
            cout << "Hit and sunk!" << endl;
            break;
        case 2:
            cout << "Already sunk!" << endl;
            break;
        default:
            cout << "Error in result!" << endl;
            break;
        }
    }

    cout << "All ships have been sunk! Game over." << endl;

    return 0;
}
