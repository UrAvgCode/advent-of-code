// --- Day 9: Encoding Error ---

#include "solver.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::uint64_t> parser(std::ifstream &file) {
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
            if (preamble.contains(numbers[i] - numbers[j])) {
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
    Solver solver(2020, 9, "Encoding Error");

    auto numbers = solver.parse_file(parser);
    solver(part_one, numbers);
    solver(part_two, numbers);

    return 0;
}
