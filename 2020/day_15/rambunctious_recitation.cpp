// --- Day 15: Rambunctious Recitation ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::uint64_t> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::stringstream stream;
    stream << file.rdbuf();

    std::vector<std::uint64_t> starting_numbers;
    for (std::string token; getline(stream, token, ',');) {
        starting_numbers.push_back(std::stoull(token));
    }

    return starting_numbers;
}

std::uint64_t get_nth_number(const std::vector<std::uint64_t> &starting_numbers, std::size_t n) {
    std::unordered_map<std::uint64_t, std::size_t> spoken_numbers;
    for (auto i = 0; i < starting_numbers.size() - 1; i++) {
        spoken_numbers[starting_numbers[i]] = i + 1;
    }

    auto prev_number = starting_numbers.back();
    for (auto i = starting_numbers.size(); i < n; i++) {
        auto next_number = spoken_numbers.contains(prev_number) ? i - spoken_numbers[prev_number] : 0;
        spoken_numbers[prev_number] = i;
        prev_number = next_number;
    }

    return prev_number;
}

int main() {
    std::string filename = "../../input/2020/day_15/input.txt";
    auto starting_numbers = parse_file(filename);

    std::cout << "--- Day 15: Rambunctious Recitation ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << get_nth_number(starting_numbers, 2020) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << get_nth_number(starting_numbers, 30000000) << std::endl;
    benchmark::end(start);

    return 0;
}
