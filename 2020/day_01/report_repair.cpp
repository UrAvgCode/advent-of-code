// --- Day 1: Report Repair ---

#include "solver.h"

#include <fstream>
#include <set>
#include <string>

std::set<int> parser(std::ifstream &file) {
    std::set<int> entries;
    for (std::string line; getline(file, line);) {
        entries.insert(std::stoi(line));
    }

    return entries;
}

int part_one(const std::set<int> &entries) {
    for (auto entry: entries) {
        int missing = 2020 - entry;
        if (entries.contains(missing)) {
            return entry * missing;
        }
    }

    return -1;
}

int part_two(const std::set<int> &entries) {
    for (auto first = entries.begin(); first != entries.end(); ++first) {
        for (auto second = std::next(first); second != entries.end(); ++second) {
            int missing = 2020 - *first - *second;
            if (entries.contains(missing)) {
                return *first * *second * missing;
            }
        }
    }

    return -1;
}

int main() {
    Solver solver(2020, 2, "Report Repair");

    auto entries = solver.parse_file(parser);
    solver(part_one, entries);
    solver(part_two, entries);

    return 0;
}
