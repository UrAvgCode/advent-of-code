// --- Day 3: Toboggan Trajectory ---

#include "solver.h"

#include <fstream>
#include <string>
#include <vector>

std::pair<std::vector<char>, std::size_t> parser(std::ifstream &file) {
    std::size_t width = 0;
    std::vector<char> trees;
    for (std::string line; getline(file, line); width = line.size()) {
        trees.insert(trees.end(), line.begin(), line.end());
    }

    return {trees, width};
}

int count_trees(const std::pair<std::vector<char>, std::size_t> &tree_map, const int right, const int down) {
    auto [trees, width] = tree_map;

    int x = 0;
    int tree_count = 0;
    const int height = static_cast<int>(trees.size() / width);
    for (int y = down; y < height; y += down) {
        x = (x + right) % static_cast<int>(width);
        if (trees[y * width + x] == '#') {
            tree_count++;
        }
    }

    return tree_count;
}

std::uint64_t part_two(const std::pair<std::vector<char>, std::size_t> &tree_map) {
    const std::array<std::pair<int, int>, 5> slopes = {{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}}};

    std::uint64_t tree_product = 1;
    for (const auto &[right, down]: slopes) {
        tree_product *= count_trees(tree_map, right, down);
    }

    return tree_product;
}

int main() {
    Solver solver(2020, 3, "Toboggan Trajectory");

    auto tree_map = solver.parse_file(parser);
    solver(count_trees, tree_map, 3, 1);
    solver(part_two, tree_map);

    return 0;
}
