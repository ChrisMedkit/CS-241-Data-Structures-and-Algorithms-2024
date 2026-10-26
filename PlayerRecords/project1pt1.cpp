#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <stdio.h>

using namespace std;

// Struct for player info
struct Player {
    string fullName;
    double rating;
    string team;
    int jerseyNumber;
    int goalsScored;
};

//comparing players
bool comparePlayersByGoals(const Player& a, const Player& b) {
    return a.goalsScored > b.goalsScored;
}

// writing player to players.txt
void writePlayersToFile(const vector<Player>& players) {
    ofstream outFile("players.txt");
    if (!outFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    for (const auto& player : players) {
        outFile << player.fullName << endl
            << player.rating << endl
            << player.team << endl
            << player.jerseyNumber << endl
            << player.goalsScored << endl;
    }

    outFile.close();
}

// printing player details
void printPlayerDetails(const Player& player) {
    cout << "Name     : " << player.fullName << endl;
    cout << "Rating   : " << player.rating << endl;
    cout << "Team     : " << player.team << endl;
    cout << "Number   : " << player.jerseyNumber << endl;
    cout << "Goals    : " << player.goalsScored << endl;
    cout << "-------------------------------------" << endl;
}

int main() {
    vector<Player> players = {
        {"Christian Pulisic", 82.0, "Chelsea F.C.", 3, 79},
        {"Cristiano Ronaldo", 91.0, "Manchester United.F.C.", 7, 504},
        {"Mo(Mohamed) Salah", 90.0, "Liverpool F.C.", 11, 320},
        {"Lionel Messi", 93.0, "Paris Saint-Germain", 30, 511}
    };

    // Sort players
    sort(players.begin(), players.end(), comparePlayersByGoals);

    // Write player info to the file
    writePlayersToFile(players);

    // Print player details
    for (const auto& player : players) {
        printPlayerDetails(player);
    }

    return 0;
}