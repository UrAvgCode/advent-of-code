// --- Day 7: Handy Haversacks ---

#include "solver.h"

#include <algorithm>
#include <fstream>
#include <queue>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using BagMap = std::unordered_map<std::string, std::vector<std::pair<int, std::string>>>;

BagMap parser(std::ifstream &file) {
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

std::uint32_t part_one(const BagMap &bag_map) {
    return std::ranges::count_if(std::views::keys(bag_map), [&bag_map](const auto &initial_bag) {
        auto bag_queue = std::queue<std::string>({initial_bag});
        while (!bag_queue.empty()) {
            auto current_bag = bag_queue.front();
            bag_queue.pop();

            for (const auto &containing_bag: std::views::values(bag_map.at(current_bag))) {
                if (containing_bag == "shiny gold") {
                    return true;
                }

                bag_queue.push(containing_bag);
            }
        }

        return false;
    });
}

std::uint32_t part_two(const BagMap &bag_map) {
    std::uint32_t count_of_bags = 0;

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
    Solver solver(2020, 7, "Handy Haversacks");

    auto bag_map = solver.parse_file(parser);
    solver(part_one, bag_map);
    solver(part_two, bag_map);

    return 0;
}
