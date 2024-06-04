// --- Day 6: Custom Customs ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::vector<std::string>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

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

int part_one(const std::vector<std::vector<std::string>> &groups) {
    int sum_of_counts = 0;

    for (const auto &answers: groups) {
        std::unordered_set<char> answer_set;
        for (const auto &answer: answers) {
            answer_set.insert(answer.begin(), answer.end());
        }

        sum_of_counts += static_cast<int>(answer_set.size());
    }

    return sum_of_counts;
}

int part_two(const std::vector<std::vector<std::string>> &groups) {
    int sum_of_counts = 0;

    for (const auto &answers: groups) {
        std::unordered_map<char, int> answer_map;
        auto group_size = answers.size();

        for (const auto &answer: answers) {
            for (char c: answer) {
                answer_map[c]++;
            }
        }

        for (const auto &count: std::views::values(answer_map)) {
            if (count == group_size) {
                sum_of_counts++;
            }
        }
    }

    return sum_of_counts;
}

int main() {
    std::string filename = "../../input/2020/day_06/input.txt";
    auto groups = parse_file(filename);

    std::cout << "--- Day 6: Custom Customs ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(groups) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(groups) << std::endl;
    benchmark::end(start);

    return 0;
}
