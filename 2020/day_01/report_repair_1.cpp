// --- Day 1: Report Repair --- Part One ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> entrySet;
    string line;

    ifstream fileReader("2020/day_01/report_repair_input");

    while (getline(fileReader, line)) {
        int entry = stoi(line);
        int missing = 2020 - entry;

        if (entrySet.find(missing) != entrySet.end()) {
            cout << "Part 1: " << entry * missing << "\n";
        } else {
            entrySet.insert(entry);
        }
    }

    fileReader.close();
}
