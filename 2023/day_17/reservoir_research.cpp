// --- Day 17: Reservoir Research ---

#include "reservoir_research.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>

std::pair<std::vector<std::uint8_t>, int> parse_file(const std::string &filename) {
    auto heat_map = std::vector<std::uint8_t>();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::string line;
    int width = 0;
    while (std::getline(file, line)) {
        if (width == 0) {
            width = static_cast<int>(line.length());
            heat_map.reserve(width * width);
        }

        for (auto block: line) {
            heat_map.push_back(static_cast<std::uint8_t>(block - '0'));
        }
    }

    return {heat_map, width};
}

int get_minimum_heat_loss(const std::vector<std::uint8_t> &heat_map, int width,
                          int braking_duration = 0, int maximum_speed = 3) {

    auto crucible_queue = std::priority_queue<Crucible, std::vector<Crucible>, std::greater<>>();
    auto crucible_history = std::unordered_set<Crucible>(10'000);
    crucible_queue.push({0, 0, 0, 0, 0, 0});

    int height = static_cast<int>(heat_map.size()) / width;
    auto destination = std::pair{width - 1, height - 1};

    while (!crucible_queue.empty()) {
        auto crucible = crucible_queue.top();
        crucible_queue.pop();

        if (crucible_history.count(crucible) == 1) {
            continue;
        }
        crucible_history.insert(crucible);
        auto [x, y, x_dir, y_dir, speed, heat_loss] = crucible;

        if (std::pair{crucible.x, crucible.y} == destination && crucible.speed >= braking_duration) {
            return crucible.heat_loss;
        }

        if (speed >= braking_duration || speed == 0) {
            if (x_dir == 0) {
                for (int i: {1, -1}) {
                    if (x + i >= 0 && x + i < width) {
                        auto additional_heat_loss = heat_map[y * width + x + i];
                        crucible_queue.push({x + i, y, i, 0, 1, heat_loss + additional_heat_loss});
                    }
                }
            }

            if (y_dir == 0) {
                for (int i: {1, -1}) {
                    if (y + i >= 0 && y + i < height) {
                        auto additional_heat_loss = heat_map[(y + i) * width + x];
                        crucible_queue.push({x, y + i, 0, i, 1, heat_loss + additional_heat_loss});
                    }
                }
            }
        }

        if (speed < maximum_speed) {
            auto new_x = x + x_dir;
            auto new_y = y + y_dir;

            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                auto additional_heat_loss = heat_map[new_y * width + new_x];
                crucible_queue.push({new_x, new_y, x_dir, y_dir, speed + 1, heat_loss + additional_heat_loss});
            }
        }

    }

    return -1;
}

int main() {
    auto filename = "2023/day_17/reservoir_research_input";
    auto [heat_map, width] = parse_file(filename);

    std::cout << "Part 1: " << get_minimum_heat_loss(heat_map, width) << std::endl;
    std::cout << "Part 2: " << get_minimum_heat_loss(heat_map, width, 4, 10) << std::endl;

    return 0;
}
