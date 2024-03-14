// --- Day 2: Password Philosophy --- Part One ---

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    int treeCount = 0;
    string line;

    ifstream fileReader("2020/day_03/toboggan_trajectory_input");

    int index = 0;
    getline(fileReader, line);
    while (getline(fileReader, line)) {
        index = (index + 3) % (int) line.size();
        if (line[index] == '#') {
            treeCount++;
        }
    }

    cout << "Part 1: " << treeCount << "\n";

    fileReader.close();
}
