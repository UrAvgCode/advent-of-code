// --- Day 6: Custom Customs ---

#include "solver.h"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::vector<std::string>> parser(std::ifstream &file) {
    std::vector<std::string> answers;
    std::vector<std::vector<std::string>> groups;
    for (std::string line; getline(file, line);) {
        if (line.empty()) {
            groups.push_back(answers);
            answers = {};
        } else {
            answers.push_back(line);
        }
    }
    groups.push_back(answers);

    return groups;
}

std::uint32_t part_one(const std::vector<std::vector<std::string>> &groups) {
    return std::transform_reduce(groups.begin(), groups.end(), 0u, std::plus<>(), [](const auto &answers) {
        std::unordered_set<char> answer_set;
        for (const auto &answer: answers) {
            answer_set.insert(answer.begin(), answer.end());
        }

        return answer_set.size();
    });
}

std::uint32_t part_two(const std::vector<std::vector<std::string>> &groups) {
    return std::transform_reduce(groups.begin(), groups.end(), 0u, std::plus<>(), [](const auto &answers) {
        std::unordered_map<char, int> answer_map;
        auto group_size = answers.size();

        for (const auto &answer: answers) {
            for (char c: answer) {
                ++answer_map[c];
            }
        }

        return std::ranges::count_if(std::views::values(answer_map), [&group_size](const auto &count) {
            return count == group_size;
        });
    });
}

int main() {
    Solver solver(2020, 6, "Custom Customs");

    auto groups = solver.parse_file(parser);
    solver(part_one, groups);
    solver(part_two, groups);

    return 0;
}
