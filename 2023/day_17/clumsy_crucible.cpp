// --- Day 17: Clumsy Crucible ---

#include "crucible.h"
#include "solver.h"

#include <fstream>
#include <queue>
#include <unordered_set>
#include <vector>

std::pair<std::vector<std::uint8_t>, std::size_t> parser(std::ifstream &file) {
    std::size_t width;
    std::vector<std::uint8_t> heat_map;
    for (std::string line; getline(file, line); width = line.length()) {
        for (const auto block: line) {
            heat_map.emplace_back(block - '0');
        }
    }

    return {heat_map, width};
}

int get_heat_loss(const std::vector<std::uint8_t> &heat_map, const std::size_t width, const int break_duration,
                  const int max_speed) {
    auto crucible_queue =
            std::priority_queue<clumsy_crucible::crucible, std::vector<clumsy_crucible::crucible>, std::greater<>>();
    auto crucible_history = std::unordered_set<clumsy_crucible::crucible>(10'000);
    crucible_queue.emplace(0, 0, 0, 0, 0, 0);

    const auto height = heat_map.size() / width;
    const auto destination = std::pair{width - 1, height - 1};

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
                        const auto additional_heat_loss = heat_map[y * width + x + i];
                        crucible_queue.emplace(x + i, y, i, 0, 1, heat_loss + additional_heat_loss);
                    }
                }
            }

            if (dy == 0) {
                for (int i: {1, -1}) {
                    if (y + i >= 0 && y + i < height) {
                        crucible_queue.emplace(x, y + i, 0, i, 1, heat_loss + heat_map[(y + i) * width + x]);
                    }
                }
            }
        }

        if (speed < max_speed) {
            auto next_x = x + dx;
            auto next_y = y + dy;

            if (next_x >= 0 && next_x < width && next_y >= 0 && next_y < height) {
                crucible_queue.emplace(next_x, next_y, dx, dy, speed + 1,
                                       heat_loss + heat_map[next_y * width + next_x]);
            }
        }
    }

    return -1;
}

int main() {
    Solver solver(2023, 17, "Clumsy Crucible");

    auto [heat_map, width] = solver.parse_file(parser);
    solver(get_heat_loss, heat_map, width, 0, 3);
    solver(get_heat_loss, heat_map, width, 4, 10);

    return 0;
}
