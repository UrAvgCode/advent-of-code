// --- Day 12: Rain Risk ---

#include "benchmark.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<char, int>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<std::pair<char, int>> navigation_instructions;
    for (std::string line; getline(file, line);) {
        char action = line[0];
        int amount = std::stoi(line.substr(1));
        navigation_instructions.emplace_back(action, amount);
    }

    return navigation_instructions;
}

double part_one(const std::vector<std::pair<char, int>> &navigation_instructions) {
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

int main() {
    std::string filename = "../../input/2020/day_12/input.txt";
    auto navigation_instructions = parse_file(filename);

    std::cout << "--- Day 12: Rain Risk ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(navigation_instructions) << std::endl;
    benchmark::end(start);

    return 0;
}
