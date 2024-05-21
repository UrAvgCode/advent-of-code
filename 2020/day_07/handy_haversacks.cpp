// --- Day 7: Handy Haversacks ---

#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <vector>

using BagMap = std::unordered_map<std::string, std::vector<std::pair<int, std::string>>>;

BagMap parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    BagMap bag_map;
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

        bag_map[key] = contains;
    }

    return bag_map;
}

bool contains_shiny_gold(const BagMap &bag_map, const std::string &initial_bag) {
    auto bag_queue = std::queue<std::string>({initial_bag});
    while (!bag_queue.empty()) {
        auto current_bag = bag_queue.front();
        bag_queue.pop();

        for (const auto &[_, containing_bag]: bag_map.at(current_bag)) {
            if (containing_bag == "shiny gold") {
                return true;
            } else {
                bag_queue.push(containing_bag);
            }
        }
    }

    return false;
}

int part_one(const BagMap &bag_map) {
    int count_of_bags = 0;
    for (const auto &[initial_bag, _]: bag_map) {
        if (contains_shiny_gold(bag_map, initial_bag)) {
            count_of_bags++;
        }
    }

    return count_of_bags;
}

int part_two(const BagMap &bag_map) {
    int count_of_bags = 0;

    auto bag_queue = std::queue<std::pair<int, std::string>>();
    bag_queue.emplace(1, "shiny gold");

    while (!bag_queue.empty()) {
        auto [current_amount, current_bag] = bag_queue.front();
        bag_queue.pop();

        count_of_bags += current_amount;

        const auto &contents = bag_map.at(current_bag);
        for (const auto &[containing_amount, containing_bag]: contents) {
            bag_queue.emplace(containing_amount * current_amount, containing_bag);
        }
    }

    return count_of_bags - 1;
}

int main() {
    std::string filename = "../../input/2020/day_07/input.txt";
    auto bag_map = parse_file(filename);

    std::cout << "--- Day 6: Custom Customs ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(bag_map) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(bag_map) << std::endl;
    benchmark::end(start);

    return 0;
}

