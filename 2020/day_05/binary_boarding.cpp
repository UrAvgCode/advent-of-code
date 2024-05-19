// --- Day 5: Binary Boarding ---

#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

std::vector<std::array<char, 10>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<std::array<char, 10>> boarding_passes;
    for (std::string line; getline(file, line);) {
        std::array<char, 10> pass{};
        std::copy_n(line.begin(), pass.size(), pass.begin());
        boarding_passes.push_back(pass);
    }

    return boarding_passes;
}

std::set<int> get_seat_ids(const std::vector<std::array<char, 10>> &boarding_passes) {
    std::set<int> seat_ids;
    for (const auto &pass: boarding_passes) {
        int row = 0;
        int row_count = 128;
        int column = 0;
        int column_count = 8;

        for (char c: pass) {
            if (c == 'F') {
                row_count /= 2;
            } else if (c == 'B') {
                row_count /= 2;
                row += row_count;
            } else if (c == 'R') {
                column_count /= 2;
                column += column_count;
            } else if (c == 'L') {
                column_count /= 2;
            }
        }

        int seat_id = 8 * row + column;
        seat_ids.insert(seat_id);
    }

    return seat_ids;
}

int part_one(const std::vector<std::array<char, 10>> &boarding_passes) {
    return *get_seat_ids(boarding_passes).rbegin();
}

int part_two(const std::vector<std::array<char, 10>> &boarding_passes) {
    auto seat_ids = get_seat_ids(boarding_passes);
    for (auto it = std::next(seat_ids.begin()); it != seat_ids.end(); it++) {
        if (*std::prev(it) != *it - 1) {
            return *it - 1;
        }
    }

    return -1;
}

int main() {
    std::string filename = "../../input/2020/day_05/input.txt";
    auto boarding_passes = parse_file(filename);

    std::cout << "--- Day 5: Binary Boarding ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(boarding_passes) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(boarding_passes) << std::endl;
    benchmark::end(start);
}

