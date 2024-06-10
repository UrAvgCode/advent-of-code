// --- Day 12: Rain Risk ---

#include "solver.h"

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::pair<char, int>> parser(std::ifstream &file) {
    std::vector<std::pair<char, int>> navigation_instructions;
    for (std::string line; getline(file, line);) {
        char action = line[0];
        int amount = std::stoi(line.substr(1));
        navigation_instructions.emplace_back(action, amount);
    }

    return navigation_instructions;
}

int part_one(const std::vector<std::pair<char, int>> &navigation_instructions) {
    int x = 0;
    int y = 0;
    int direction = 0;

    for (const auto &[action, amount]: navigation_instructions) {
        switch (action) {
            case 'N':
                y += amount;
                break;
            case 'S':
                y -= amount;
                break;
            case 'E':
                x += amount;
                break;
            case 'W':
                x -= amount;
                break;
            case 'L':
                direction = (direction + amount) % 360;
                break;
            case 'R':
                direction = (direction + 360 - amount) % 360;
                break;
            case 'F':
                x += static_cast<int>(std::cos(direction * (M_PI / 180.0))) * amount;
                y += static_cast<int>(std::sin(direction * (M_PI / 180.0))) * amount;
                break;
            default:
                std::cerr << "invalid action: " << action << std::endl;
        }
    }

    return std::abs(x) + std::abs(y);
}

int part_two(const std::vector<std::pair<char, int>> &navigation_instructions) {
    int waypoint_x = 10;
    int waypoint_y = 1;
    int x = 0;
    int y = 0;

    for (const auto &[action, amount]: navigation_instructions) {
        switch (action) {
            case 'N':
                waypoint_y += amount;
                break;
            case 'S':
                waypoint_y -= amount;
                break;
            case 'E':
                waypoint_x += amount;
                break;
            case 'W':
                waypoint_x -= amount;
                break;
            case 'L': {
                int sin = static_cast<int>(std::sin(amount * (M_PI / 180.0)));
                int cos = static_cast<int>(std::cos(amount * (M_PI / 180.0)));

                int next_x = waypoint_x * cos + waypoint_y * -sin;
                int next_y = waypoint_x * sin + waypoint_y * cos;

                waypoint_x = next_x;
                waypoint_y = next_y;
                break;
            }
            case 'R': {
                int sin = static_cast<int>(std::sin(amount * (M_PI / 180.0)));
                int cos = static_cast<int>(std::cos(amount * (M_PI / 180.0)));

                int next_x = waypoint_x * cos + waypoint_y * sin;
                int next_y = waypoint_x * -sin + waypoint_y * cos;

                waypoint_x = next_x;
                waypoint_y = next_y;
                break;
            }
            case 'F':
                x += waypoint_x * amount;
                y += waypoint_y * amount;
                break;
            default:
                std::cerr << "invalid action: " << action << std::endl;
        }
    }

    return std::abs(x) + std::abs(y);
}

int main() {
    Solver solver(2020, 12, "Rain Risk");

    auto navigation_instructions = solver.parse_file(parser);
    solver(part_one, navigation_instructions);
    solver(part_two, navigation_instructions);

    return 0;
}
