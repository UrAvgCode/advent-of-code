// --- Day 7: Handy Haversacks ---

#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> bags;
    for (std::string line; getline(file, line);) {
        std::vector<std::string> tokens;

        std::stringstream stream(line);
        std::string token;

        while (stream >> token) {
            tokens.push_back(token);
        }

        auto key = tokens[0] + " " + tokens[1];
        std::vector<std::pair<int, std::string>> contains;
        for (int i = 4; i < tokens.size(); i += 4) {
            if (tokens[i] == "no") {
                break;
            }

            int amount = std::stoi(tokens[i]);
            auto bag = tokens[i + 1] + " " + tokens[i + 2];
            contains.emplace_back(amount, bag);
        }

        bags[key] = contains;
    }

    return bags;
}

int contains_shiny_gold(const std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> &bags_map,
                        const std::string &bag) {
    auto bag_queue = std::queue<std::string>({bag});
    while (!bag_queue.empty()) {
        auto current_bag = bag_queue.front();
        bag_queue.pop();

        for (const auto &[amount, containing_bag]: bags_map.at(current_bag)) {
            if (containing_bag == "shiny gold") {
                return 1;
            } else {
                bag_queue.push(containing_bag);
            }
        }

    }

    return 0;
}

int part_one(const std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> &bags_map) {
    int count_of_shiny_gold_bags = 0;
    for (const auto &[initial_bag, contains]: bags_map) {
        count_of_shiny_gold_bags += contains_shiny_gold(bags_map, initial_bag);
    }

    return count_of_shiny_gold_bags;
}

int part_two(const std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> &bags_map) {
    int count_of_bags = 0;

    auto bag_queue = std::queue<std::pair<int, std::string>>();
    bag_queue.emplace(1, "shiny gold");

    while (!bag_queue.empty()) {
        auto [current_amount, current_bag] = bag_queue.front();
        bag_queue.pop();

        count_of_bags += current_amount;

        const auto &contents = bags_map.at(current_bag);
        for (const auto &[containing_amount, containing_bag]: contents) {
            bag_queue.emplace(containing_amount * current_amount, containing_bag);
        }
    }

    return count_of_bags - 1;
}

int main() {
    std::string filename = "../../input/2020/day_07/input.txt";
    auto bags = parse_file(filename);

    std::cout << "--- Day 6: Custom Customs ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(bags) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(bags) << std::endl;
    benchmark::end(start);

    return 0;
}

