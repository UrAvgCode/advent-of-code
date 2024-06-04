// --- Day 2: Password Philosophy ---

#include "benchmark.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using PasswordList = std::vector<std::tuple<std::string, char, int, int>>;

PasswordList parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    PasswordList passwords;
    for (std::string line; getline(file, line);) {
        auto hyphen_index = line.find('-');
        auto space_index = line.find(' ');

        int lowest = stoi(line.substr(0, hyphen_index));
        int highest = stoi(line.substr(hyphen_index + 1, space_index - hyphen_index));

        char character = line[space_index + 1];
        auto password = line.substr(space_index + 4);

        passwords.emplace_back(password, character, lowest, highest);
    }

    return passwords;
}

int part_one(const PasswordList &passwords) {
    int valid_password_count = 0;
    for (const auto &[password, character, lowest, highest]: passwords) {
        auto char_count = static_cast<int>(std::ranges::count(password.begin(), password.end(), character));
        if (char_count >= lowest && char_count <= highest) {
            valid_password_count++;
        }
    }
    return valid_password_count;
}

int part_two(const PasswordList &passwords) {
    int valid_password_count = 0;
    for (const auto &[password, character, pos_one, pos_two]: passwords) {
        if ((password[pos_one - 1] == character) != (password[pos_two - 1] == character)) {
            valid_password_count++;
        }
    }
    return valid_password_count;
}

int main() {
    std::string filename = "../../input/2020/day_02/input.txt";
    auto passwords = parse_file(filename);

    std::cout << "--- Day 2: Password Philosophy ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(passwords) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 1: " << part_two(passwords) << std::endl;
    benchmark::end(start);
}
