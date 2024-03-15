// --- Day 6: Custom Customs --- Part Two ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    int sumOfCounts = 0;
    int groupSize = 0;
    unordered_map<char, int> questions;

    ifstream fileReader("2020/day_06/custom_customs_input");

    string line;
    while (getline(fileReader, line)) {
        if (line.empty()) {
            for(auto [key, count]: questions) {
                if (count == groupSize) {
                    sumOfCounts += 1;
                }
            }

            groupSize = 0;
            questions.clear();
        } else {
            groupSize += 1;
            for (char c: line) {
                if(questions.find(c) == questions.end()) {
                    questions[c] = 1;
                } else {
                    questions[c] += 1;
                }
            }
        }
    }

    for(auto [key, count]: questions) {
        if (count == groupSize) {
            sumOfCounts += 1;
        }
    }

    fileReader.close();

    cout << "Part 2: " << sumOfCounts << "\n";
}

