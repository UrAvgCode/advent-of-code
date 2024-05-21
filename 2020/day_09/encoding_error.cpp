// --- Day 9: Encoding Error ---

#include "benchmark.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::uint64_t> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<std::uint64_t> numbers;
    for (std::string line; getline(file, line);) {
        numbers.push_back(std::stoull(line));
    }

    return numbers;
}

std::uint64_t part_one(const std::vector<std::uint64_t> &numbers) {
    for (int i = 25; i < numbers.size(); i++) {
        auto preamble = std::unordered_set<uint64_t>(numbers.begin() + i - 25, numbers.begin() + i);
        for (int j = i - 25; j < i; j++) {
            if (preamble.find(numbers[i] - numbers[j]) != preamble.end()) {
                break;
            } else if (j == i - 1) {
                return numbers[i];
            }
        }
    }

    return 0;
}

std::uint64_t part_two(const std::vector<std::uint64_t> &numbers) {
    std::uint64_t invalid_number = part_one(numbers);

    int start_pointer = 0;
    int end_pointer = 0;

    std::uint64_t window_sum = numbers[0];
    while (true) {
        if (window_sum == invalid_number) {
            auto min_value = *std::min_element(numbers.begin() + start_pointer, numbers.begin() + end_pointer);
            auto max_value = *std::max_element(numbers.begin() + start_pointer, numbers.begin() + end_pointer);
            return min_value + max_value;
        } else if (window_sum > invalid_number) {
            window_sum -= numbers[start_pointer];
            start_pointer++;
        } else {
            end_pointer++;
            window_sum += numbers[end_pointer];
        }
    }
}

int main() {
    std::string filename = "../../input/2020/day_09/input.txt";
    auto numbers = parse_file(filename);

    std::cout << "--- Day 9: Encoding Error ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(numbers) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(numbers) << std::endl;
    benchmark::end(start);

    return 0;
}

