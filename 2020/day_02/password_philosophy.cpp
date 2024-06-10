// --- Day 2: Password Philosophy ---

#include "solver.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using PasswordPolicy = std::tuple<int, int, char, std::string>;

std::vector<PasswordPolicy> parser(std::ifstream &file) {
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
    Solver solver(2020, 2, "Password Philosophy");

    auto password_policies = solver.parse_file(parser);
    solver(part_one, password_policies);
    solver(part_two, password_policies);

    return 0;
}
