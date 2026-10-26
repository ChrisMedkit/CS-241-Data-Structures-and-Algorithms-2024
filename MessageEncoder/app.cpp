#include <iostream>
#include <fstream>
#include <stack>
#include <sstream>
#include <vector>
#include <algorithm>

//reverses every other word
std::string reverseOddWords(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    //making every other word encoded
    for (size_t i = 0; i < words.size(); ++i) {
        if (i % 2 == 0) { 
            std::reverse(words[i].begin(), words[i].end());
        }
    }

    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i != 0) oss << " ";
        oss << words[i];
    }
    return oss.str();
}

//encoding the message
void encodeLetter(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream infile(inputFile);
    std::ofstream outfile(outputFile);
    std::stack<std::string> linesStack;

    std::string line;
    while (std::getline(infile, line)) {
        linesStack.push(reverseOddWords(line));
    }

    while (!linesStack.empty()) {
        outfile << linesStack.top() << std::endl;
        linesStack.pop();
    }
}

//reading and printing the message
void readEncodedLetter(const std::string& file) {
    std::ifstream infile(file);
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
}

int main() {
    // giving the prompt to write the message
    std::cout << "Enter your message (Press enter twice to confirm):" << std::endl;
    std::ofstream originalFile("original.txt");
    std::string userLine;
    while (true) {
        std::getline(std::cin, userLine);
        if (userLine.empty()) break;
        originalFile << userLine << std::endl;
    }

    //encodes the message and sends it to encoded.txt
    encodeLetter("original.txt", "encoded.txt");

    //prints out encoded message

    std::cout << "Encoded Letter:" << std::endl;
    readEncodedLetter("encoded.txt");

    return 0;
}
