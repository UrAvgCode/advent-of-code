// --- Day 1: Report Repair ---

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
            if (entries[i] + entries[j] == 2020) {
                cout << "Part 1: " << entries[i] * entries[j] << "\n";
            }
        }
    }
}
