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
    const auto regex_pattern = std::regex(R"(mul\(\d+,\d+\))");
    const auto regex = std::sregex_iterator(instructions.begin(), instructions.end(), regex_pattern);
    const auto regex_end = std::sregex_iterator();

    return std::transform_reduce(regex, regex_end, 0ull, std::plus<>(), [](auto &it) {
        auto instruction = it.str();
        const std::size_t comma_index = instruction.find(',');

        auto factor_one = std::stoull(instruction.substr(4, comma_index - 4));
        auto factor_two = std::stoull(instruction.substr(comma_index + 1, instruction.size() - comma_index + 2));

        return factor_one * factor_two;
    });
}

int main() {
    Solver solver(2024, 3, "Mull It Over");

    const auto instructions = solver.parse_file(parser);
    solver(part_one, instructions);

    return 0;
}
