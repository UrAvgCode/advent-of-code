// --- Day 17: Reservoir Research ---

#include "reservoir_research.h"
#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

std::pair<std::vector<std::uint8_t>, int> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    int width = 0;
    std::vector<std::uint8_t> heat_map;
    for (std::string line; getline(file, line);) {
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

int get_heat_loss(const std::vector<std::uint8_t> &heat_map, int width, int break_duration = 0, int max_speed = 3) {
    auto crucible_queue = std::priority_queue<Crucible, std::vector<Crucible>, std::greater<>>();
    auto crucible_history = std::unordered_set<Crucible>(10'000);
    crucible_queue.emplace(0, 0, 0, 0, 0, 0);

    int height = static_cast<int>(heat_map.size()) / width;
    auto destination = std::pair{width - 1, height - 1};

    while (!crucible_queue.empty()) {
        const auto crucible = crucible_queue.top();
        crucible_queue.pop();

        if (crucible_history.count(crucible) == 1) {
            continue;
        }

        crucible_history.insert(crucible);
        auto [x, y, dx, dy, speed, heat_loss] = crucible;

        if (std::tie(x, y) == destination && crucible.speed >= break_duration) {
            return heat_loss;
        }

        if (speed >= break_duration || speed == 0) {
            if (dx == 0) {
                for (int i: {1, -1}) {
                    if (x + i >= 0 && x + i < width) {
                        auto additional_heat_loss = heat_map[y * width + x + i];
                        crucible_queue.emplace(x + i, y, i, 0, 1, heat_loss + additional_heat_loss);
                    }
                }
            }

            if (dy == 0) {
                for (int i: {1, -1}) {
                    if (y + i >= 0 && y + i < height) {
                        auto additional_heat_loss = heat_map[(y + i) * width + x];
                        crucible_queue.emplace(x, y + i, 0, i, 1, heat_loss + additional_heat_loss);
                    }
                }
            }
        }

        if (speed < max_speed) {
            auto new_x = x + dx;
            auto new_y = y + dy;

            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                auto additional_heat_loss = heat_map[new_y * width + new_x];
                crucible_queue.emplace(new_x, new_y, dx, dy, speed + 1, heat_loss + additional_heat_loss);
            }
        }
    }

    return -1;
}

int main() {
    auto filename = "../../input/2023/day_17/input.txt";
    auto [heat_map, width] = parse_file(filename);

    std::cout << "--- Day 17: Reservoir Research ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << get_heat_loss(heat_map, width) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << get_heat_loss(heat_map, width, 4, 10) << std::endl;
    benchmark::end(start);

    return 0;
}
