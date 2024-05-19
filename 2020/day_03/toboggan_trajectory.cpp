// --- Day 3: Toboggan Trajectory ---

#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::pair<std::vector<char>, int> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    int width = 0;
    std::vector<char> trees;
    for (std::string line; getline(file, line);) {
        if (width == 0) width = static_cast<int>(line.size());
        trees.insert(trees.end(), line.begin(), line.end());
    }

    return {trees, width};
}

int count_trees(const std::pair<std::vector<char>, int> &tree_map, int right, int down) {
    auto [trees, width] = tree_map;

    int x = 0;
    int tree_count = 0;
    int height = static_cast<int>(trees.size() / width);
    for (int y = down; y < height; y += down) {
        x = (x + right) % width;
        if (trees[y * width + x] == '#') {
            tree_count++;
        }
    }

    return tree_count;
}

std::uint64_t part_two(const std::pair<std::vector<char>, int> &tree_map) {
    const std::array<std::pair<int, int>, 5> slopes = {{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}}};

    std::uint64_t tree_product = 1;
    for (const auto &slope: slopes) {
        tree_product *= static_cast<std::uint64_t>(count_trees(tree_map, slope.first, slope.second));
    }

    return tree_product;
}

int main() {
    std::string filename = "../../input/2020/day_03/input.txt";
    auto tree_map = parse_file(filename);

    std::cout << "--- Day 3: Toboggan Trajectory ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << count_trees(tree_map, 3, 1) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(tree_map) << std::endl;
    benchmark::end(start);
}
