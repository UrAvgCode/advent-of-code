// --- Day 17: Conway Cubes ---

#include "conway_cubes.h"
#include "solver.h"

#include <fstream>
#include <string>

std::pair<std::vector<char>, std::size_t> parser(std::ifstream &file) {
    std::size_t width = 0;
    std::vector<char> slice;
    for (std::string line; std::getline(file, line); width = line.size()) {
        slice.insert(slice.end(), line.begin(), line.end());
    }

    return {slice, width};
}

int part_one(const std::vector<char> &slice, std::size_t width) {
    auto hypercube = Hypercube<3>({width, slice.size() / width, 1});
    for (std::size_t i = 0; i < slice.size(); ++i) {
        int x = static_cast<int>(i % width);
        int y = static_cast<int>(i / width);
        hypercube.set({x, y, 0}, slice[i] == '#');
    }

    for (std::size_t i = 0; i < 6; ++i) {
        auto next_hypercube = Hypercube<3>({hypercube.size(0) + 2, hypercube.size(1) + 2, hypercube.size(2) + 2});
        for (std::size_t j = 0; j < next_hypercube.size(); ++j) {
            int x = static_cast<int>(j % next_hypercube.size(0));
            int y = static_cast<int>((j / next_hypercube.size(0)) % next_hypercube.size(1));
            int z = static_cast<int>(j / (next_hypercube.size(0) * next_hypercube.size(1)));

            int neighbors = 0;
            for (std::size_t k = 0; k < 3 * 3 * 3; ++k) {
                int dx = static_cast<int>(k % 3) - 1;
                int dy = static_cast<int>((k / 3) % 3) - 1;
                int dz = static_cast<int>(k / (3 * 3)) - 1;
                if (dx == 0 && dy == 0 && dz == 0) {
                    continue;
                }

                if (hypercube.get({x + dx - 1, y + dy - 1, z + dz - 1})) {
                    ++neighbors;
                }
            }

            if (hypercube.get({x - 1, y - 1, z - 1})) {
                if (neighbors == 2 || neighbors == 3) {
                    next_hypercube.set({x, y, z}, true);
                }
            } else {
                if (neighbors == 3) {
                    next_hypercube.set({x, y, z}, true);
                }
            }
        }

        hypercube = next_hypercube;
    }

    int sum = 0;
    for (bool value: hypercube.data()) {
        sum += value;
    }

    return sum;
}

int part_two(const std::vector<char> &slice, std::size_t width) {
    auto hypercube = Hypercube<4>({width, slice.size() / width, 1, 1});
    for (std::size_t i = 0; i < slice.size(); ++i) {
        int x = static_cast<int>(i % width);
        int y = static_cast<int>(i / width);
        hypercube.set({x, y, 0, 0}, slice[i] == '#');
    }

    for (std::size_t i = 0; i < 6; ++i) {
        auto next_hypercube = Hypercube<4>(
                {hypercube.size(0) + 2, hypercube.size(1) + 2, hypercube.size(2) + 2, hypercube.size(3) + 2});

        for (std::size_t j = 0; j < next_hypercube.size(); ++j) {
            int x = static_cast<int>(j % next_hypercube.size(0));
            int y = static_cast<int>((j / next_hypercube.size(0)) % next_hypercube.size(1));
            int z = static_cast<int>((j / (next_hypercube.size(0) * next_hypercube.size(1))) % next_hypercube.size(2));
            int w = static_cast<int>(j / (next_hypercube.size(0) * next_hypercube.size(1) * next_hypercube.size(2)));

            int neighbors = 0;
            for (std::size_t k = 0; k < 3 * 3 * 3 * 3; ++k) {
                int dx = static_cast<int>(k % 3) - 1;
                int dy = static_cast<int>((k / 3) % 3) - 1;
                int dz = static_cast<int>((k / (3 * 3)) % 3) - 1;
                int dw = static_cast<int>(k / (3 * 3 * 3)) - 1;
                if (dx == 0 && dy == 0 && dz == 0 && dw == 0) {
                    continue;
                }

                if (hypercube.get({x + dx - 1, y + dy - 1, z + dz - 1, w + dw - 1})) {
                    ++neighbors;
                }
            }

            if (hypercube.get({x - 1, y - 1, z - 1, w - 1})) {
                if (neighbors == 2 || neighbors == 3) {
                    next_hypercube.set({x, y, z, w}, true);
                }
            } else {
                if (neighbors == 3) {
                    next_hypercube.set({x, y, z, w}, true);
                }
            }
        }

        hypercube = next_hypercube;
    }

    int sum = 0;
    for (bool value: hypercube.data()) {
        sum += value;
    }

    return sum;
}

int main() {
    Solver solver(2020, 17, "Conway Cubes");

    auto [slice, width] = solver.parse_file(parser);
    solver(part_one, slice, width);
    solver(part_two, slice, width);

    return 0;
}
