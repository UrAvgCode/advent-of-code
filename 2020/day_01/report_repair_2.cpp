// --- Day 1: Report Repair --- Part Two ---

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> entries;
    string entry;

    ifstream fileReader("2020/day_01/report_repair_input");

    while (getline(fileReader, entry)) {
        entries.push_back(std::stoi(entry));
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
