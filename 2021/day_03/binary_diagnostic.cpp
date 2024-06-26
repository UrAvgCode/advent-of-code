// --- Day 3: Binary Diagnostic ---

#include "solver.h"

#include <bitset>
#include <fstream>
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
    const auto number_of_bits = diagnostic_report[0].size();
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
    auto filter_diagnostic_report = [](std::vector<std::string> report, auto bit_criteria) {
        for (std::size_t i = 0; report.size() > 1; ++i) {
            std::vector<std::string> next_diagnostic_report;

            int ones = 0;
            int zeros = 0;
            for (const auto &binary_number: report) {
                ones += binary_number[i] == '1';
                zeros += binary_number[i] == '0';
            }

            const char significant_bit = bit_criteria(ones, zeros) ? '1' : '0';
            for (const auto &binary_number: report) {
                if (binary_number[i] == significant_bit) {
                    next_diagnostic_report.push_back(binary_number);
                }
            }

            report = next_diagnostic_report;
        }

        return std::bitset<32>(report[0]).to_ulong();
    };

    const auto oxygen_generator_rating = filter_diagnostic_report(diagnostic_report, std::greater_equal{});
    const auto co2_scrubber_rating = filter_diagnostic_report(diagnostic_report, std::less{});

    return oxygen_generator_rating * co2_scrubber_rating;
}

int main() {
    Solver solver(2021, 3, "Binary Diagnostic");

    const auto diagnostic_report = solver.parse_file(parser);
    solver(part_one, diagnostic_report);
    solver(part_two, diagnostic_report);

    return 0;
}
