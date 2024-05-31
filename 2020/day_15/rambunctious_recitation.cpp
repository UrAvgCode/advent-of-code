// --- Day 15: Rambunctious Recitation ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<int> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::stringstream stream;
    stream << file.rdbuf();

    std::vector<int> starting_numbers;
    for (std::string token; getline(stream, token, ',');) {
        starting_numbers.push_back(std::stoi(token));
    }

    return starting_numbers;
}

std::uint64_t part_one(const std::vector<int> &starting_numbers) {
    std::unordered_map<int, int> spoken_numbers;

    int prev_number = starting_numbers.back();
    for (int i = 1; i < 2020; i++) {
        if (i < starting_numbers.size()) {
            spoken_numbers[starting_numbers[i - 1]] = i;
        } else if (spoken_numbers.contains(prev_number)) {
            int difference = i - spoken_numbers[prev_number];
            spoken_numbers[prev_number] = i;
            prev_number = difference;
        } else {
            spoken_numbers[prev_number] = i;
            prev_number = 0;
        }
    }

    return prev_number;
}

int main() {
    std::string filename = "../../input/2020/day_15/input.txt";
    auto starting_numbers = parse_file(filename);

    std::cout << "--- Day 15: Rambunctious Recitation ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(starting_numbers) << std::endl;
    benchmark::end(start);

    return 0;
}
