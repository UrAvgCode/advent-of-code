// --- Day 6: Custom Customs --- Part Two ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int countQuestions(unordered_map<char, int> &questions, int groupSize) {
    int sumOfCounts = 0;
    for (auto [key, count]: questions) {
        if (count == groupSize) {
            sumOfCounts++;
        }
    }
    return sumOfCounts;
}

int main() {
    int sumOfCounts = 0;
    int groupSize = 0;
    unordered_map<char, int> questions;

    ifstream fileReader("2020/day_06/custom_customs_input");

    string line;
    while (getline(fileReader, line)) {
        if (line.empty()) {
            sumOfCounts += countQuestions(questions, groupSize);
            groupSize = 0;
            questions.clear();
        } else {
            groupSize += 1;
            for (char c: line) {
                questions[c]++;
            }
        }
    }

    sumOfCounts += countQuestions(questions, groupSize);

    fileReader.close();

    cout << "Part 2: " << sumOfCounts << "\n";
}

