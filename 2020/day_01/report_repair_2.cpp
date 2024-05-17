// --- Day 1: Report Repair --- Part Two ---

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> entries;

    string line;
    ifstream fileReader("input/2020/day_01/input.txt");
    while (getline(fileReader, line)) {
        entries.push_back(stoi(line));
    }

    fileReader.close();

    for (int i = 0; i < entries.size(); i++) {
        for (int j = i + 1; j < entries.size(); j++) {
            for (int k = j + 1; k < entries.size(); k++) {
                if (entries[i] + entries[j] + entries[k] == 2020) {
                    cout << "Part 2: " << entries[i] * entries[j] * entries[k] << "\n";
                }
            }
        }
    }
}
