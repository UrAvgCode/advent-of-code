// --- Day 8: Handheld Halting ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<std::string, int>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

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
    std::string filename = "../../input/2020/day_08/input.txt";
    auto instructions = parse_file(filename);

    std::cout << "--- Day 8: Handheld Halting ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(instructions) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(instructions) << std::endl;
    benchmark::end(start);

    return 0;
}
