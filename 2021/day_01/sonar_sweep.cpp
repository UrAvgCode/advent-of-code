// --- Day 1: Sonar Sweep ---

#include "solver.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> parser(std::ifstream &file) {
    std::vector<int> depths;
    for (std::string line; getline(file, line);) {
        depths.push_back(std::stoi(line));
    }

    return depths;
}

int part_one(const std::vector<int> &depths) {
    int count = 0;
    for (std::size_t i = 0; i < depths.size() - 1; ++i) {
        count += depths[i] < depths[i + 1];
    }

    return count;
}

int part_two(const std::vector<int> &depths) {
    int count = 0;
    for (std::size_t i = 0; i < depths.size() - 3; ++i) {
        count += depths[i] < depths[i + 3];
    }

    return count;
}

int main() {
    Solver solver(2021, 1, "Sonar Sweep");

    const auto depths = solver.parse_file(parser);
    solver(part_one, depths);
    solver(part_two, depths);

    return 0;
}
