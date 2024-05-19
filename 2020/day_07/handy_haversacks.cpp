// --- Day 7: Handy Haversacks ---

#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::unordered_map<std::string, std::unordered_set<std::string>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> bags;
    for (std::string line; getline(file, line);) {
        std::vector<std::string> tokens;

        std::stringstream stream(line);
        std::string token;

        while (stream >> token) {
            tokens.push_back(token);
        }

        auto key = tokens[0] + " " + tokens[1];
        auto contains = std::unordered_set<std::string>();
        for (int i = 5; i < tokens.size(); i += 4) {
            if (tokens[i] == "other") {
                break;
            }

            auto bag = tokens[i] + " " + tokens[i + 1];
            contains.insert(bag);
        }

        bags[key] = contains;
    }

    return bags;
}

int contains_shiny_gold(const std::unordered_map<std::string, std::unordered_set<std::string>> &bags_map, const std::string &bag) {
    auto bag_queue = std::queue<std::string>({bag});
    while (!bag_queue.empty()) {
        auto current_bag = bag_queue.front();
        bag_queue.pop();

        for(const auto &containing_bag : bags_map.at(current_bag)) {
            if (containing_bag == "shiny gold") {
                return 1;
            } else {
                bag_queue.push(containing_bag);
            }
        }

    }

    return 0;
}

int part_one(const std::unordered_map<std::string, std::unordered_set<std::string>> &bags_map) {
    int count_of_shiny_gold_bags = 0;
    for (const auto &[initial_bag, contains]: bags_map) {
        count_of_shiny_gold_bags += contains_shiny_gold(bags_map, initial_bag);
    }

    return count_of_shiny_gold_bags;
}

int main() {
    std::string filename = "../../input/2020/day_07/input.txt";
    auto bags = parse_file(filename);

    std::cout << "--- Day 6: Custom Customs ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(bags) << std::endl;
    benchmark::end(start);

    return 0;
}

