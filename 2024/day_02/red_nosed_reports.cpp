// --- Day 2: Red-Nosed Reports ---

#include "solver.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>

std::vector<std::vector<int>> parser(std::ifstream &file) {
    std::vector<std::vector<int>> reports;

    for (std::string line; getline(file, line);) {
        std::istringstream string_stream(line);

        int number;
        std::vector<int> report;
        while (string_stream >> number) {
            report.push_back(number);
        }

        reports.push_back(report);
    }

    return reports;
}

std::uint64_t part_one(const std::vector<std::vector<int>> &reports) {
    const auto number_of_safe_reports = std::ranges::count_if(reports, [](auto &report) {
        if (report[0] < report[1]) {
            for (std::size_t i = 1; i < report.size(); ++i) {
                if (report[i] <= report[i - 1] || report[i] - report[i - 1] > 3) {
                    return false;
                }
            }
        } else {
            for (std::size_t i = 1; i < report.size(); ++i) {
                if (report[i] >= report[i - 1] || report[i - 1] - report[i] > 3) {
                    return false;
                }
            }
        }

        return true;
    });

    return number_of_safe_reports;
}

int main() {
    Solver solver(2024, 2, "Red-Nosed Reports");

    const auto reports = solver.parse_file(parser);
    solver(part_one, reports);

    return 0;
}
