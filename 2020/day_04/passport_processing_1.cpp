// --- Day 4: Passport Processing --- Part One ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    int validPassportCount = 0;

    ifstream fileReader("2020/day_04/passport_processing_input");

    string line;
    unordered_set<string> fields;
    while (getline(fileReader, line)) {
        while (!line.empty()) {
            int colonIndex = (int) line.find(':');
            int spaceIndex = (int) line.find(' ');

            string field = line.substr(0, colonIndex);
            if(field != "cid") {
                fields.insert(field);
            }
            line = line.substr(spaceIndex + 1, line.size() - (spaceIndex + 1));

            if(spaceIndex == -1) {
                break;
            }
        }

        if(line.empty()) {
            if(fields.size() == 7) {
                validPassportCount++;
            }
            fields.clear();
        }
    }

    cout << "Part 1: " << validPassportCount << "\n";

    fileReader.close();
}
