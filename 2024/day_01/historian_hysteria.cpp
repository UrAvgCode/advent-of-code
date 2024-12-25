// --- Day 1: Historian Hysteria ---

#include "solver.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>
#include <string>
#include <unordered_map>

std::array<std::vector<int>, 2> parser(std::ifstream &file) {
    std::vector<int> left_list;
    std::vector<int> right_list;

    for (std::string line; getline(file, line);) {
        left_list.push_back(std::stoi(line.substr(0, 5)));
        right_list.push_back(std::stoi(line.substr(8, 5)));
    }

    return {left_list, right_list};
}

int part_one(const std::vector<int> &left_list, const std::vector<int> &right_list) {
    auto left_list_sorted = left_list;
    auto right_list_sorted = right_list;

    std::ranges::sort(left_list_sorted);
    std::ranges::sort(right_list_sorted);

    const int total_distance = std::transform_reduce(
            left_list_sorted.begin(), left_list_sorted.end(), right_list_sorted.begin(), 0, std::plus<>(),
            [](const int left_number, const int right_number) { return std::abs(left_number - right_number); });

    return total_distance;
}

int part_two(const std::vector<int> &left_list, const std::vector<int> &right_list) {
    std::unordered_map<int, int> counts;
    for (const int &value: right_list) {
        ++counts[value];
    }

    const int similarity_score = std::transform_reduce(left_list.begin(), left_list.end(), 0, std::plus<>(),
                                                       [&counts](const int value) { return value * counts[value]; });

    return similarity_score;
}

int main() {
    Solver solver(2024, 1, "Historian Hysteria");

    const auto [left_list, right_list] = solver.parse_file(parser);
    solver(part_one, left_list, right_list);
    solver(part_two, left_list, right_list);

    return 0;
}
