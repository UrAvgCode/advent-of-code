// --- Day 17: Clumsy Crucible ---

#include "crucible.h"
#include "solver.h"

#include <fstream>
#include <queue>
#include <unordered_set>
#include <vector>

using heap_t = std::priority_queue<clumsy_crucible::crucible, std::vector<clumsy_crucible::crucible>, std::greater<>>;

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

std::uint16_t get_heat_loss(const std::vector<std::uint8_t> &heat_map, const std::size_t width,
                            const std::uint16_t break_duration, const std::uint16_t max_speed) {
    auto crucible_history = std::unordered_set<clumsy_crucible::crucible>(1ull << 10ull);

    auto crucible_queue = heap_t();
    crucible_queue.emplace();

    const auto height = heat_map.size() / width;
    const auto destination_x = width - 1;
    const auto destination_y = height - 1;

    while (!crucible_queue.empty()) {
        const auto crucible = crucible_queue.top();
        crucible_queue.pop();

        if (crucible_history.contains(crucible)) {
            continue;
        }

        crucible_history.insert(crucible);
        const auto &[x, y, dx, dy, speed, heat_loss] = crucible;

        if (x == destination_x && y == destination_y && crucible.speed >= break_duration) {
            return heat_loss;
        }

        if (speed >= break_duration || speed == 0) {
            if (dx == 0) {
                for (const auto ndx: {1, -1}) {
                    if (x + ndx >= 0 && x + ndx < width) {
                        const auto additional_heat_loss = heat_map[y * width + x + ndx];
                        crucible_queue.emplace(x + ndx, y, ndx, 0, 1, heat_loss + additional_heat_loss);
                    }
                }
            }

            if (dy == 0) {
                for (const auto ndy: {1, -1}) {
                    if (y + ndy >= 0 && y + ndy < height) {
                        crucible_queue.emplace(x, y + ndy, 0, ndy, 1, heat_loss + heat_map[(y + ndy) * width + x]);
                    }
                }
            }
        }

        if (speed < max_speed) {
            const auto nx = x + dx;
            const auto ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                crucible_queue.emplace(nx, ny, dx, dy, speed + 1, heat_loss + heat_map[ny * width + nx]);
            }
        }
    }

    return 0;
}

int main() {
    Solver solver(2023, 17, "Clumsy Crucible");

    auto [heat_map, width] = solver.parse_file(parser);
    solver(get_heat_loss, heat_map, width, 0, 3);
    solver(get_heat_loss, heat_map, width, 4, 10);

    return 0;
}
