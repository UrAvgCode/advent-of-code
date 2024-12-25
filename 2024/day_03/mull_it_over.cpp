// --- Day 3: Mull It Over ---

#include "solver.h"

#include <fstream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

std::string parser(std::ifstream &file) {
    std::vector<std::vector<int>> reports;

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::uint64_t part_one(const std::string &instructions) {
    const std::regex regex_pattern(R"(mul\((\d+),(\d+)\))");
    const auto regex_begin = std::sregex_iterator(instructions.begin(), instructions.end(), regex_pattern);
    const auto regex_end = std::sregex_iterator();

    return std::transform_reduce(regex_begin, regex_end, 0ull, std::plus<>(), [](const auto &match) {
        auto factor_one = std::stoull(match[1].str());
        auto factor_two = std::stoull(match[2].str());
        return factor_one * factor_two;
    });
}

int main() {
    Solver solver(2024, 3, "Mull It Over");

    const auto instructions = solver.parse_file(parser);
    solver(part_one, instructions);

    return 0;
}
