// --- Day 10: Adapter Array ---

#include "benchmark.h"

#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

std::set<int> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::set<int> joltage_adapters;
    for (std::string line; getline(file, line);) {
        joltage_adapters.insert(std::stoi(line));
    }

    return joltage_adapters;
}

int part_one(const std::set<int> &joltage_adapters) {
    int one_jolt_differences = 0;
    int three_jolt_differences = 1;

    int previous_joltage = 0;
    for (auto output_joltage: joltage_adapters) {
        if (output_joltage - previous_joltage == 1) {
            one_jolt_differences++;
        } else {
            three_jolt_differences++;
        }
        previous_joltage = output_joltage;
    }

    return one_jolt_differences * three_jolt_differences;
}

std::uint64_t part_two(const std::set<int> &joltage_adapters) {
    std::array<int, 5> possibilities = {1, 1, 2, 4, 7};
    std::uint64_t arrangements = 1;

    int previous_joltage = 0;
    int consecutive_ones = 0;
    for (auto output_joltage: joltage_adapters) {
        if (output_joltage - previous_joltage == 1) {
            consecutive_ones++;
        } else {
            arrangements *= possibilities[consecutive_ones];
            consecutive_ones = 0;
        }
        previous_joltage = output_joltage;
    }

    return arrangements * possibilities[consecutive_ones];
}

int main() {
    std::string filename = "../../input/2020/day_10/input.txt";
    auto joltage_adapters = parse_file(filename);

    std::cout << "--- Day 10: Adapter Array ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(joltage_adapters) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(joltage_adapters) << std::endl;
    benchmark::end(start);

    return 0;
}
