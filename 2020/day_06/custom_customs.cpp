// --- Day 6: Custom Customs ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int countQuestions(unordered_map<char, int> &questions, int groupSize) {
    int count = 0;
    for (const auto &question: questions) {
        if (question.second == groupSize) {
            count++;
        }
    }
    return count;
}

int main() {
    int sumOfCountsOne = 0;
    int sumOfCountsTwo = 0;
    int groupSize = 0;
    unordered_map<char, int> questions;

    ifstream fileReader("2020/day_06/custom_customs_input");

    string line;
    while (getline(fileReader, line)) {
        if (line.empty()) {
            sumOfCountsOne += (int) questions.size();
            sumOfCountsTwo += countQuestions(questions, groupSize);
            groupSize = 0;
            questions.clear();
        } else {
            groupSize += 1;
            for (char c: line) {
                questions[c]++;
            }
        }
    }

    sumOfCountsOne += (int) questions.size();
    sumOfCountsTwo += countQuestions(questions, groupSize);

    fileReader.close();

    cout << "Part 1: " << sumOfCountsOne << endl;
    cout << "Part 2: " << sumOfCountsTwo << endl;

    return 0;
}

