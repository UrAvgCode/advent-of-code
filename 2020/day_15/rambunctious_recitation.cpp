// --- Day 15: Rambunctious Recitation ---

#include "solver.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::uint64_t> parser(std::fstream &file) {
    std::stringstream stream;
    stream << file.rdbuf();

    std::vector<std::uint64_t> starting_numbers;
    for (std::string token; getline(stream, token, ',');) {
        starting_numbers.push_back(std::stoull(token));
    }

    return starting_numbers;
}

std::uint64_t get_nth_number(const std::vector<std::uint64_t> &starting_numbers, std::size_t n) {
    std::unordered_map<std::uint64_t, std::size_t> spoken_numbers(n);
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
    Solver solver(2020, 15, "Rambunctious Recitation");

    auto starting_numbers = solver.parse_file(parser);
    solver(get_nth_number, starting_numbers, 2020);
    solver(get_nth_number, starting_numbers, 30000000);

    return 0;
}
