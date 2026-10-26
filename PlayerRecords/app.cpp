#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

// Define the Player struct
struct Player {
    std::string fullName;
    double rating;
    std::string team;
    int jerseyNumber;
    int goalsScored;

    // Constructor for easy initialization
    Player(std::string name, double rate, std::string tm, int num, int goals) :
        fullName(name), rating(rate), team(tm), jerseyNumber(num), goalsScored(goals) {}
};

// Function to read data from file
std::vector<Player> readPlayersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Player> players;
    std::string temp;

    if (!file.is_open()) {
        std::cerr << "Unable to open file\n";
        return players;
    }

    while (std::getline(file, temp)) {
        // Assuming each player's data spans 5 lines
        if (temp.empty()) continue; // Skip empty lines between players
        Player player(temp, 0.0, "", 0, 0);
        for (int i = 0; i < 4; ++i) {
            std::getline(file, temp);
            switch (i) {
            case 0: player.rating = std::stod(temp); break;
            case 1: player.team = temp; break;
            case 2: player.jerseyNumber = std::stoi(temp); break;
            case 3: player.goalsScored = std::stoi(temp); break;
            }
        }
        players.push_back(player);
    }
    file.close();
    return players;
}

// Function to sort players by goals scored
void sortPlayersByGoals(std::vector<Player>& players) {
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.goalsScored > b.goalsScored;
        });
}

// Modified printPlayers function for specific output format and reversed order
void printPlayers(const std::vector<Player>& players) {
    for (auto it = players.rbegin(); it != players.rend(); ++it) {
        std::cout << "Name     : " << it->fullName << "\n"
            << "Rating   : " << it->rating << "\n"
            << "Team     : " << it->team << ".\n"
            << "Number   : " << it->jerseyNumber << "\n"
            << "Goals    : " << it->goalsScored << "\n"
            << "-------------------------------------\n";
    }
}

int main() {
    const std::string filename = "players.txt";

    // Reading data from the file, sorting, and printing
    std::vector<Player> players = readPlayersFromFile(filename);
    sortPlayersByGoals(players);
    printPlayers(players);

    return 0;
}
