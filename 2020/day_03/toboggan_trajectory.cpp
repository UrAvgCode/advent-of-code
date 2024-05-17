// --- Day 3: Toboggan Trajectory ---

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int countTrees(const vector<string> &treeMap, int right, int down) {
    int treeCount = 0;
    int index = 0;
    for (int y = down; y < treeMap.size(); y += down) {
        const string &line = treeMap[y];
        index = (index + right) % (int) line.size();

        if (line[index] == '#') {
            treeCount++;
        }
    }

    return treeCount;
}

int main() {
    vector<string> treeMap;
    string line;

    ifstream fileReader("input/2020/day_03/input.txt");

    while (getline(fileReader, line)) {
        treeMap.push_back(line);
    }

    int slopes[5][2] = {
            {1, 1},
            {3, 1},
            {5, 1},
            {7, 1},
            {1, 2},
    };

    int treeCounts[5];
    for (int i = 0; i < 5; i++) {
        treeCounts[i] = countTrees(treeMap, slopes[i][0], slopes[i][1]);
    }

    unsigned int treeProduct = 1;
    for (int treeCount: treeCounts) {
        treeProduct *= treeCount;
    }

    cout << "Part 1: " << treeCounts[1] << "\n";
    cout << "Part 2: " << treeProduct << "\n";

    fileReader.close();
}
