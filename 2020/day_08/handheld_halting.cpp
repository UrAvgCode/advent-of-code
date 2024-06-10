// --- Day 8: Handheld Halting ---

#include "solver.h"

#include <fstream>
#include <string>
#include <vector>

std::vector<std::pair<std::string, int>> parser(std::ifstream &file) {
    std::vector<std::pair<std::string, int>> instructions;
    for (std::string line; getline(file, line);) {
        auto space_index = line.find(' ');
        auto operation = line.substr(0, space_index);
        auto argument = std::stoi(line.substr(space_index + 1));
        instructions.emplace_back(operation, argument);
    }

    return instructions;
}

int part_one(const std::vector<std::pair<std::string, int>> &instructions) {
    auto visited_indexes = std::vector<bool>(instructions.size(), false);

    int index = 0;
    int accumulator = 0;

    while (true) {
        if (visited_indexes[index]) {
            return accumulator;
        } else {
            visited_indexes[index] = true;
            auto [operation, argument] = instructions[index];

            if (operation == "acc") {
                accumulator += argument;
                index++;
            } else if (operation == "jmp") {
                index += argument;
            } else {
                index++;
            }
        }
    }
}

int part_two(const std::vector<std::pair<std::string, int>> &instructions) {
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i].first == "acc") {
            continue;
        }

        auto visited_indexes = std::vector<bool>(instructions.size(), false);

        int index = 0;
        int accumulator = 0;

        while (true) {
            if (index == instructions.size()) {
                return accumulator;
            } else if (visited_indexes[index]) {
                break;
            } else {
                visited_indexes[index] = true;
                auto [operation, argument] = instructions[index];

                if (operation == "acc") {
                    accumulator += argument;
                    index++;
                } else if (operation == "jmp") {
                    index += (index == i) ? 1 : argument;
                } else {
                    index += (index == i) ? argument : 1;
                }
            }
        }
    }

    return -1;
}

int main() {
    Solver solver(2020, 8, "Handheld Halting");

    auto instructions = solver.parse_file(parser);
    solver(part_one, instructions);
    solver(part_two, instructions);

    return 0;
}
