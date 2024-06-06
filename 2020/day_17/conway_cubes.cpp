// --- Day 17: Conway Cubes ---

#include "conway_cubes.h"
#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <string>

std::pair<std::vector<char>, std::size_t> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::size_t width = 0;
    std::vector<char> slice;
    for (std::string line; std::getline(file, line) && !line.empty();) {
        if (width == 0)
            width = line.size();
        slice.insert(slice.end(), line.begin(), line.end());
    }

    return {slice, width};
}

std::uint32_t part_one(const std::vector<char> &slice, std::size_t width) {
    auto conway_cube = Cube(width, slice.size() / width, 1);
    for (std::size_t i = 0; i < slice.size(); ++i) {
        int x = static_cast<int>(i % width);
        int y = static_cast<int>(i / width);
        conway_cube.set(x, y, 0, slice[i]);
    }

    for (std::size_t i = 0; i < 6; ++i) {
        auto new_cube = Cube(conway_cube.width() + 2, conway_cube.height() + 2, conway_cube.depth() + 2);
        for (std::size_t j = 0; j < new_cube.size(); ++j) {
            int x = static_cast<int>(j % new_cube.width());
            int y = static_cast<int>((j / new_cube.width()) % new_cube.height());
            int z = static_cast<int>(j / (new_cube.width() * new_cube.height()));

            int neighbors = 0;
            for (std::size_t k = 0; k < 3 * 3 * 3; ++k) {
                int dx = static_cast<int>(k % 3) - 1;
                int dy = static_cast<int>((k / 3) % 3) - 1;
                int dz = static_cast<int>(k / (3 * 3)) - 1;
                if (dx == 0 && dy == 0 && dz == 0) {
                    continue;
                }

                if (conway_cube.get(x + dx - 1, y + dy - 1, z + dz - 1) == '#') {
                    ++neighbors;
                }
            }

            if (conway_cube.get(x - 1, y - 1, z - 1) == '#') {
                if (neighbors == 2 || neighbors == 3) {
                    new_cube.set(x, y, z, '#');
                }
            } else {
                if (neighbors == 3) {
                    new_cube.set(x, y, z, '#');
                }
            }
        }

        conway_cube = new_cube;
    }

    std::uint64_t count = 0;
    for (auto value: conway_cube.data()) {
        if (value == '#') {
            ++count;
        }
    }

    return count;
}

int main() {
    std::string filename = "../../input/2020/day_17/input.txt";
    auto [slice, width] = parse_file(filename);

    std::cout << "--- Day 17: Conway Cubes ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(slice, width) << std::endl;
    benchmark::end(start);

    return 0;
}
