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
        int hyphenIndex = line.find('-');
        int spaceIndex = line.find(' ');

        int indexOne = stoi(line.substr(0, hyphenIndex));
        int indexTwo = stoi(line.substr(hyphenIndex + 1, spaceIndex - hyphenIndex));

        char character = line[spaceIndex + 1];
        string password = line.substr(spaceIndex + 4, line.size() - (spaceIndex + 4));

        int charCount = 0;
        if (password[indexOne - 1] == character) {
            charCount++;
        }
        if (password[indexTwo - 1] == character) {
            charCount++;
        }

        if (charCount == 1) {
            validPasswordCount++;
        }
    }

    cout << "Part 2: " << validPasswordCount << "\n";

    fileReader.close();
}
