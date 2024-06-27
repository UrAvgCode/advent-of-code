// --- Day 3: Binary Diagnostic ---

#include "solver.h"

#include <algorithm>
#include <bitset>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

std::vector<std::string> parser(std::ifstream &file) {
    std::vector<std::string> diagnostic_report;
    for (std::string line; getline(file, line);) {
        diagnostic_report.push_back(line);
    }

    return diagnostic_report;
}

std::uint32_t part_one(const std::vector<std::string> &diagnostic_report) {
    const auto number_of_bits = diagnostic_report.front().size();
    std::vector ones(number_of_bits, 0);
    std::vector zeros(number_of_bits, 0);

    for (const auto &binary_number: diagnostic_report) {
        for (std::size_t i = 0; i < binary_number.size(); ++i) {
            ones[i] += binary_number[i] == '1';
            zeros[i] += binary_number[i] == '0';
        }
    }

    std::uint32_t gamma_rate = 0;
    std::uint32_t epsilon_rate = 0;
    for (std::size_t i = 0; i < number_of_bits; ++i) {
        const std::uint32_t shift = ones.size() - i - 1;
        const std::uint32_t bit_mask = 1u << shift;
        if (ones[i] > zeros[i]) {
            gamma_rate |= bit_mask;
        } else {
            epsilon_rate |= bit_mask;
        }
    }

    return gamma_rate * epsilon_rate;
}

std::uint32_t part_two(const std::vector<std::string> &diagnostic_report) {
    auto compute_rating = [&](const std::function<bool(std::size_t, std::size_t)> &bit_criteria) {
        auto filtered_report = diagnostic_report;
        for (std::size_t i = 0; filtered_report.size() > 1; ++i) {
            const std::size_t ones = std::ranges::count_if(filtered_report, [i](const auto &binary) { return binary[i] == '1'; });
            const std::size_t zeros = filtered_report.size() - ones;

            const char significant_bit = bit_criteria(ones, zeros) ? '1' : '0';
            std::erase_if(filtered_report, [i, significant_bit](const std::string &binary_number) {
                return binary_number[i] != significant_bit;
            });
        }

        return std::bitset<32>(filtered_report.front()).to_ulong();
    };

    const auto oxygen_generator_rating = compute_rating(std::greater_equal{});
    const auto co2_scrubber_rating = compute_rating(std::less{});

    return oxygen_generator_rating * co2_scrubber_rating;
}

int main() {
    Solver solver(2021, 3, "Binary Diagnostic");

    const auto diagnostic_report = solver.parse_file(parser);
    solver(part_one, diagnostic_report);
    solver(part_two, diagnostic_report);

    return 0;
}
