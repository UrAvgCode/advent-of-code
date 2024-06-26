// --- Day 2: Dive! ---

#include "solver.h"

#include <fstream>
#include <string>
#include <vector>

std::vector<std::pair<std::string, int>> parser(std::ifstream &file) {
    std::vector<std::pair<std::string, int>> commands;
    for (std::string line; getline(file, line);) {
        std::istringstream line_stream(line);

        int value;
        std::string command;
        line_stream >> command >> value;
        commands.emplace_back(command, value);
    }

    return commands;
}

int part_one(const std::vector<std::pair<std::string, int>> &commands) {
    int depth = 0;
    int horizontal_position = 0;
    for (const auto &[command, amount]: commands) {
        if (command == "forward") {
            horizontal_position += amount;
        } else if (command == "up") {
            depth -= amount;
        } else if (command == "down") {
            depth += amount;
        }
    }

    return depth * horizontal_position;
}

int part_two(const std::vector<std::pair<std::string, int>> &commands) {
    int aim = 0;
    int depth = 0;
    int horizontal_position = 0;
    for (const auto &[command, amount]: commands) {
        if (command == "forward") {
            depth += aim * amount;
            horizontal_position += amount;
        } else if (command == "up") {
            aim -= amount;
        } else if (command == "down") {
            aim += amount;
        }
    }

    return depth * horizontal_position;
}

int main() {
    Solver solver(2021, 2, "Dive!");

    const auto commands = solver.parse_file(parser);
    solver(part_one, commands);
    solver(part_two, commands);

    return 0;
}
