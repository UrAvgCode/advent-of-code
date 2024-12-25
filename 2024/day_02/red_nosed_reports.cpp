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

std::uint64_t part_two(const std::vector<std::vector<int>> &reports) {
    const auto number_of_safe_reports = std::ranges::count_if(reports, [](const auto &report) {
        for (std::size_t i = 0; i < report.size(); ++i) {
            auto modified_report = report;
            modified_report.erase(modified_report.begin() + i);

            for (std::size_t j = 1; j < modified_report.size(); ++j) {
                if (modified_report[j] <= modified_report[j - 1] || modified_report[j] - modified_report[j - 1] > 3) {
                    break;
                }

                if (j == modified_report.size() - 1) {
                    return true;
                }
            }

            for (std::size_t j = 1; j < modified_report.size(); ++j) {
                if (modified_report[j] >= modified_report[j - 1] || modified_report[j - 1] - modified_report[j] > 3) {
                    break;
                }

                if (j == modified_report.size() - 1) {
                    return true;
                }
            }
        }

        return false;
    });

    return number_of_safe_reports;
}

int main() {
    Solver solver(2024, 2, "Red-Nosed Reports");

    const auto reports = solver.parse_file(parser);
    solver(part_one, reports);
    solver(part_two, reports);

    return 0;
}
