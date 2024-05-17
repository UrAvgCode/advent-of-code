// --- Day 1: Report Repair --- Part One ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> entry_set;
    int multiplied_entries = -1;

    string line;
    ifstream file("input/2020/day_01/input.txt");
    while (getline(file, line)) {
        int entry = stoi(line);
        int missing = 2020 - entry;

        if (entry_set.find(missing) != entry_set.end()) {
            multiplied_entries = entry * missing;
            break;
        } else {
            entry_set.insert(entry);
        }
    }
    file.close();

    cout << "Part 1: " << multiplied_entries << endl;
}
