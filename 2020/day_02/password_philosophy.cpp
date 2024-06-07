// --- Day 2: Password Philosophy ---

#include "benchmark.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using PasswordPolicy = std::tuple<int, int, char, std::string>;

std::vector<PasswordPolicy> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (file.fail()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<PasswordPolicy> passwords;
    for (std::string line; getline(file, line);) {
        std::stringstream stream(line);

        int min, max;
        char character;
        std::string password;
        char dummy;

        stream >> min >> dummy >> max >> character >> dummy >> password;
        passwords.emplace_back(min, max, character, password);
    }

    return passwords;
}

std::size_t part_one(const std::vector<PasswordPolicy> &password_policies) {
    return std::ranges::count_if(password_policies, [](const auto &policy) {
        const auto &[min, max, character, password] = policy;
        auto char_count = std::ranges::count(password, character);
        return char_count >= min && char_count <= max;
    });
}

std::size_t part_two(const std::vector<PasswordPolicy> &password_policies) {
    return std::ranges::count_if(password_policies, [](const auto &policy) {
        const auto &[pos_one, pos_two, character, password] = policy;
        return (password[pos_one - 1] == character) != (password[pos_two - 1] == character);
    });
}

int main() {
    std::string filename = "../../input/2020/day_02/input.txt";
    auto password_policies = parse_file(filename);

    std::cout << "--- Day 2: Password Philosophy ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(password_policies) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(password_policies) << std::endl;
    benchmark::end(start);
}
