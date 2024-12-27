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

std::uint32_t part_one(const std::vector<std::string> &word_map) {
    const auto width = word_map[0].size();
    const auto height = word_map.size();

    const auto check_direction = [&](const int x, const int y, const int dx, const int dy) {
        const auto word = std::string{word_map[y][x], word_map[y + dy][x + dx], word_map[y + 2 * dy][x + 2 * dx],
                                      word_map[y + 3 * dy][x + 3 * dx]};
        return word == "XMAS" || word == "SAMX";
    };

    std::uint32_t count = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x < width - 3) {
                count += check_direction(x, y, 1, 0);
            }

            if (y < height - 3) {
                count += check_direction(x, y, 0, 1);
            }

            if (y < height - 3 && x < width - 3) {
                count += check_direction(x, y, 1, 1);
                count += check_direction(x, y + 3, 1, -1);
            }
        }
    }

    return count;
}

std::uint32_t part_two(const std::vector<std::string> &word_map) {
    std::uint32_t count = 0;
    for (std::size_t y = 0; y < word_map.size() - 2; ++y) {
        for (std::size_t x = 0; x < word_map[0].size() - 2; ++x) {
            if (word_map[y + 1][x + 1] == 'A') {
                const char top_left = word_map[y][x];
                const char top_right = word_map[y][x + 2];
                const char bottom_left = word_map[y + 2][x];
                const char bottom_right = word_map[y + 2][x + 2];

                if (((top_left == 'M' && bottom_right == 'S') || (top_left == 'S' && bottom_right == 'M')) &&
                    ((top_right == 'M' && bottom_left == 'S') || (top_right == 'S' && bottom_left == 'M'))) {
                    ++count;
                }
            }
        }
    }

    return count;
}

int main() {
    Solver solver(2024, 4, "Ceres Search");

    const auto word_map = solver.parse_file(parser);
    solver(part_one, word_map);
    solver(part_two, word_map);

    return 0;
}
