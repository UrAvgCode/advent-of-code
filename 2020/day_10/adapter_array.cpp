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

    std::set<int> numbers;
    for (std::string line; getline(file, line);) {
        numbers.insert(std::stoi(line));
    }

    return numbers;
}

int part_one(const std::set<int> &numbers) {
    int one_jolt_differences = *numbers.begin();
    int three_jolt_differences = 1;

    for (auto it = std::next(numbers.begin()); it != numbers.end(); it++) {
        int jolt_difference = *it - *std::prev(it);
        if (jolt_difference == 1) {
            one_jolt_differences++;
        } else if (jolt_difference == 3) {
            three_jolt_differences++;
        }
    }

    return one_jolt_differences * three_jolt_differences;
}

std::uint64_t part_two(const std::set<int> &numbers) {
    std::array<int, 5> possibilities = {1, 1, 2, 4, 7};

    std::uint64_t arrangements = 1;
    int consecutive_ones = *numbers.begin() == 1;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*std::next(it) - *it == 1) {
            consecutive_ones++;
        } else {
            arrangements *= possibilities[consecutive_ones];
            consecutive_ones = 0;
        }
    }
    arrangements *= possibilities[consecutive_ones];

    return arrangements;
}

int main() {
    std::string filename = "../../input/2020/day_10/input.txt";
    auto numbers = parse_file(filename);

    std::cout << "--- Day 10: Adapter Array ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(numbers) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(numbers) << std::endl;
    benchmark::end(start);

    return 0;
}
