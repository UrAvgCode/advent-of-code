// --- Day 14: Docking Data ---

#include "solver.h"

#include <fstream>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

using Program = std::vector<std::pair<std::string, std::vector<std::array<std::uint64_t, 2>>>>;

Program parser(std::ifstream &file) {
    std::string mask;
    std::vector<std::array<std::uint64_t, 2>> memory;
    Program initialization_program;
    for (std::string line; std::getline(file, line);) {
        if (line.substr(0, 4) == "mask") {
            if (!memory.empty()) {
                initialization_program.emplace_back(mask, memory);
                memory = std::vector<std::array<std::uint64_t, 2>>();
            }
            mask = line.substr(7);
        } else {
            auto equals_index = line.find('=');
            auto address = std::stoull(line.substr(4, equals_index - 6));
            auto value = std::stoull(line.substr(equals_index + 2));
            memory.push_back({address, value});
        }
    }
    initialization_program.emplace_back(mask, memory);

    return initialization_program;
}

std::uint64_t part_one(const Program &initialization_program) {
    std::unordered_map<std::uint64_t, std::uint64_t> computer_memory;
    for (auto &[mask, memory]: initialization_program) {
        std::uint64_t and_mask = std::numeric_limits<std::uint64_t>::max();
        std::uint64_t or_mask = 0;
        std::uint64_t bit_mask = 1ull << 36;

        for (const auto bit: mask) {
            bit_mask >>= 1;
            if (bit == '1') {
                or_mask |= bit_mask;
            } else if (bit == '0') {
                and_mask &= ~bit_mask;
            }
        }

        for (auto &[address, value]: memory) {
            computer_memory[address] = value & and_mask | or_mask;
        }
    }

    auto memory_values = std::views::values(computer_memory);
    return std::reduce(memory_values.begin(), memory_values.end());
}

int main() {
    Solver solver(2020, 14, "Docking Data");

    auto initialization_program = solver.parse_file(parser);
    solver(part_one, initialization_program);

    return 0;
}
