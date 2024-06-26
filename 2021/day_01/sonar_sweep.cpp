// --- Day 1: Sonar Sweep ---

#include "solver.h"

#include <fstream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

std::vector<int> parser(std::ifstream &file) {
    return {std::istream_iterator<int>(file), std::istream_iterator<int>()};
}

int part_one(const std::vector<int> &depths) {
    return std::inner_product(depths.begin(), depths.end() - 1, depths.begin() + 1, 0, std::plus<>(), std::less<>());
}

int part_two(const std::vector<int> &depths) {
    return std::inner_product(depths.begin(), depths.end() - 3, depths.begin() + 3, 0, std::plus<>(), std::less<>());
}

int main() {
    Solver solver(2021, 1, "Sonar Sweep");

    const auto depths = solver.parse_file(parser);
    solver(part_one, depths);
    solver(part_two, depths);

    return 0;
}
