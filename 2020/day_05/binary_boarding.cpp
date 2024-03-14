// --- Day 5: Binary Boarding ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    int highestSeatID = 0;
    unordered_set<int> seats;

    ifstream fileReader("2020/day_05/binary_boarding_input");

    string line;
    while (getline(fileReader, line)) {
        int row = 0;
        int rowCount = 128;
        int column = 0;
        int columnCount = 8;

        for (char c: line) {
            switch (c) {
                case 'F':
                    rowCount /= 2;
                    break;
                case 'B':
                    rowCount /= 2;
                    row += rowCount;
                    break;
                case 'R':
                    columnCount /= 2;
                    column += columnCount;
                    break;
                case 'L':
                    columnCount /= 2;
                    break;
                default:
                    break;
            }

        }

        int seatID = 8 * row + column;
        seats.insert(seatID);
        if (seatID > highestSeatID) {
            highestSeatID = seatID;
        }
    }

    fileReader.close();

    int mySeatID;
    for(int i = 0; i < 1023; i++) {
        if (seats.find(i) == seats.end() && seats.find(i - 1) != seats.end() && seats.find(i + 1) != seats.end()) {
            mySeatID = i;
        }
    }

    cout << "Part 1: " << highestSeatID << "\n";
    cout << "Part 2: " << mySeatID << "\n";
}
