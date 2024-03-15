// --- Day 6: Custom Customs --- Part One ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    int sumOfCounts = 0;
    unordered_set<char> questions;

    ifstream fileReader("2020/day_06/custom_customs_input");

    string line;
    while (getline(fileReader, line)) {
        if (line.empty()) {
            sumOfCounts += (int) questions.size();
            questions.clear();
        } else {
            for (char c: line) {
                questions.insert(c);
            }
        }
    }
    sumOfCounts += (int) questions.size();

    fileReader.close();

    cout << "Part 1: " << sumOfCounts << "\n";
}

