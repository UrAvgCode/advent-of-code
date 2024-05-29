// --- Day 14: Docking Data ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

std::vector<std::pair<std::string, std::string>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<std::pair<std::string, std::string>> initialization_program;
    for(std::string line; std::getline(file, line);) {
        auto equals_index = line.find('=');
        std::string action = line.substr(0, equals_index - 1);
        std::string value = line.substr(equals_index + 2);

        if(action != "mask") {
            action = action.substr(4, action.length() - 1);
        }

        initialization_program.emplace_back(action, value);
    }

    return initialization_program;
}

std::uint64_t part_one(const std::vector<std::pair<std::string, std::string>>& initialization_program) {
    std::uint64_t and_mask = std::numeric_limits<std::uint64_t>::max();
    std::uint64_t or_mask = 0;

    std::unordered_map<std::uint64_t, std::uint64_t> memory;
    for(const auto &[action, value]: initialization_program) {
        if(action == "mask") {
            and_mask = std::numeric_limits<std::uint64_t>::max();
            or_mask = 0;

            for(std::uint64_t i = 0; i < value.size(); i++) {
                char current_bit = value[value.size() - 1 - i];
                if(current_bit == '1') {
                    or_mask = or_mask | (1ull << i);
                } else if(current_bit == '0') {
                    and_mask = and_mask & ~(1ull << i);
                }
            }
        } else {
            std::uint64_t memory_address = std::stoull(action);
            std::uint64_t memory_value = std::stoull(value);

            memory_value = memory_value & and_mask;
            memory_value = memory_value | or_mask;

            memory[memory_address] = memory_value;
        }
    }

    std::uint64_t sum_of_all_values = 0;
    for(auto &[_, value]: memory) {
        sum_of_all_values += value;
    }

    return sum_of_all_values;
}

int main() {
    std::string filename = "../../input/2020/day_14/input.txt";
    auto initialization_program = parse_file(filename);

    std::cout << "--- Day 14: Docking Data ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(initialization_program) << std::endl;
    benchmark::end(start);

    return 0;
}
