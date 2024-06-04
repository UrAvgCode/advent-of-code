// --- Day 4: Passport Processing ---

#include "benchmark.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::unordered_map<std::string, std::string>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::unordered_map<std::string, std::string> passport;
    std::vector<std::unordered_map<std::string, std::string>> passports;
    for (std::string line; getline(file, line);) {
        if (line.empty()) {
            passports.push_back(passport);
            passport = {};
        } else {
            std::stringstream stream(line);
            std::string token;

            while (stream >> token) {
                auto colon_pos = token.find(':');
                if (colon_pos != std::string::npos) {
                    auto field = token.substr(0, colon_pos);
                    auto value = token.substr(colon_pos + 1);

                    if (field != "cid") passport[field] = value;
                }
            }
        }
    }

    return passports;
}

bool validate_passport(const std::unordered_map<std::string, std::string> &passport) {
    int birth_year = stoi(passport.at("byr"));
    if (birth_year < 1920 || birth_year > 2002) return false;

    int issue_year = stoi(passport.at("iyr"));
    if (issue_year < 2010 || issue_year > 2020) return false;

    int expiration_year = stoi(passport.at("eyr"));
    if (expiration_year < 2020 || expiration_year > 2030) return false;

    auto hgt = passport.at("hgt");
    auto unit = hgt.substr(hgt.size() - 2, 2);
    int height = stoi(hgt.substr(0, hgt.size() - 2));

    if (unit == "cm" && (height < 150 || height > 193)) return false;
    if (unit == "in" && (height < 59 || height > 76)) return false;
    if (unit != "in" && unit != "cm") return false;

    auto hair_color = passport.at("hcl");
    if (hair_color[0] != '#') return false;
    for (char c: hair_color.substr(1, hair_color.size() - 1)) {
        if ((c < '0' || c > '9') && (c < 'a' || c > 'f')) return false;
    }

    const std::unordered_set<std::string> possible_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    std::string eye_color = passport.at("ecl");
    if (!possible_colors.contains(eye_color)) return false;

    std::string passport_id = passport.at("pid");
    if (passport_id.size() != 9) return false;
    if (!std::ranges::all_of(passport_id, ::isdigit)) return false;

    return true;
}

int part_one(const std::vector<std::unordered_map<std::string, std::string>> &passports) {
    int valid_passport_count = 0;
    for (const auto &passport: passports) {
        if (passport.size() == 7) {
            valid_passport_count++;
        }
    }

    return valid_passport_count;
}

int part_two(const std::vector<std::unordered_map<std::string, std::string>> &passports) {
    int valid_passport_count = 0;
    for (const auto &passport: passports) {
        if (passport.size() == 7 && validate_passport(passport)) {
            valid_passport_count++;
        }
    }

    return valid_passport_count;
}

int main() {
    std::string filename = "../../input/2020/day_04/input.txt";
    auto passports = parse_file(filename);

    std::cout << "--- Day 4: Passport Processing ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(passports) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(passports) << std::endl;
    benchmark::end(start);
}
