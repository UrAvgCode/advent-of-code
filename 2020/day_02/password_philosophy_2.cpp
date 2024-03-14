// --- Day 2: Password Philosophy --- Part Two ---

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    int validPasswordCount = 0;
    string line;

    ifstream fileReader("2020/day_02/password_philosophy_input");

    while (getline(fileReader, line)) {
        int hyphenIndex = (int) line.find('-');
        int spaceIndex = (int) line.find(' ');

        int indexOne = stoi(line.substr(0, hyphenIndex)) - 1;
        int indexTwo = stoi(line.substr(hyphenIndex + 1, spaceIndex - hyphenIndex)) - 1;

        char character = line[spaceIndex + 1];
        string password = line.substr(spaceIndex + 4, line.size() - (spaceIndex + 4));

        if ((password[indexOne] == character) != (password[indexTwo] == character)) {
            validPasswordCount++;
        }
    }

    cout << "Part 2: " << validPasswordCount << "\n";

    fileReader.close();
}
