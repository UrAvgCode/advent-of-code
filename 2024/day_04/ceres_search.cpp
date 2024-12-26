// --- Day 4: Ceres Search ---

#include "solver.h"

#include <fstream>
#include <numeric>
#include <string>
#include <vector>

std::vector<std::string> parser(std::ifstream &file) {
    std::vector<std::string> word_map;

    for (std::string line; getline(file, line);) {
        word_map.push_back(line);
    }

    return word_map;
}

std::uint64_t part_one(const std::vector<std::string> &word_map) {
    std::uint64_t horizontal_count = 0;
    for (std::size_t y = 0; y < word_map.size(); ++y) {
        for (std::size_t x = 0; x < word_map[0].size() - 3; ++x) {
            const std::string word = {word_map[y][x], word_map[y][x + 1], word_map[y][x + 2], word_map[y][x + 3]};
            if (word == "XMAS" || word == "SAMX") {
                ++horizontal_count;
            }
        }
    }

    std::uint64_t vertical_count = 0;
    for (std::size_t y = 0; y < word_map.size() - 3; ++y) {
        for (std::size_t x = 0; x < word_map[0].size(); ++x) {
            const std::string word = {word_map[y][x], word_map[y + 1][x], word_map[y + 2][x], word_map[y + 3][x]};
            if (word == "XMAS" || word == "SAMX") {
                ++vertical_count;
            }
        }
    }

    std::uint64_t diagonal_count = 0;
    for (std::size_t y = 0; y < word_map.size() - 3; ++y) {
        for (std::size_t x = 0; x < word_map[0].size() - 3; ++x) {
            const std::string word = {word_map[y][x], word_map[y + 1][x + 1], word_map[y + 2][x + 2],
                                      word_map[y + 3][x + 3]};
            if (word == "XMAS" || word == "SAMX") {
                ++diagonal_count;
            }
        }
    }

    for (std::size_t y = 3; y < word_map.size(); ++y) {
        for (std::size_t x = 3; x < word_map[0].size(); ++x) {
            const std::string word = {word_map[y][x], word_map[y - 1][x - 1], word_map[y - 2][x - 2],
                                      word_map[y - 3][x - 3]};
            if (word == "XMAS" || word == "SAMX") {
                ++diagonal_count;
            }
        }
    }

    return horizontal_count + vertical_count + diagonal_count;
}

int main() {
    Solver solver(2024, 4, "Ceres Search");

    const auto word_map = solver.parse_file(parser);
    solver(part_one, word_map);

    return 0;
}
