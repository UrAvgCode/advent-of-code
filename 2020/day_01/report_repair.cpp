// --- Day 1: Report Repair ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <set>

std::set<int> parse_file(const std::string &filename) {
    std::set<int> entries;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::string line;
    while (getline(file, line)) {
        entries.insert(std::stoi(line));
    }

    return entries;
}

int part_one(std::set<int> entries) {
    for (auto entry: entries) {
        int missing = 2020 - entry;
        if (entries.find(missing) != entries.end()) {
            return entry * missing;
        }
    }

    return -1;
}

int part_two(std::set<int> entries) {
    for (auto first = entries.begin(); first != entries.end(); first++) {
        for (auto second = std::next(first); second != entries.end(); second++) {
            int missing = 2020 - *first - *second;
            if (entries.find(missing) != entries.end()) {
                return *first * *second * missing;
            }
        }
    }

    return -1;
}

int main() {
    std::string filename = "../../input/2020/day_01/input.txt";
    auto entries = parse_file(filename);

    std::cout << "--- Day 1: Report Repair ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(entries) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(entries) << std::endl;
    benchmark::end(start);
}
