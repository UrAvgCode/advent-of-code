// --- Day 12: Hot Springs ---

#include "hot_springs.h"
#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

std::vector<ConditionRecord> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<ConditionRecord> records;
    for (std::string line; getline(file, line);) {
        auto index = line.find(' ');
        auto springs = line.substr(0, index);

        auto criteria = std::vector<std::uint8_t>();
        auto stream = std::stringstream(line.substr(index + 1));

        for (std::string temp; getline(stream, temp, ',');) {
            criteria.push_back(stoi(temp));
        }

        records.emplace_back(springs, criteria);
    }

    return records;
}

std::unordered_map<ConditionRecord, std::uint64_t> cache(5000);
std::uint64_t get_arrangements(const std::string &springs, const std::vector<std::uint8_t> &criteria, std::uint8_t size = 0) {
    if (springs.empty()) {
        return criteria.empty() || (criteria.size() == 1 && criteria[0] == size);
    }

    auto cache_key = ConditionRecord{springs, criteria, size};

    auto it = cache.find(cache_key);
    if (it != cache.end()) {
        return it->second;
    }

    std::uint64_t arrangements = 0;
    char first_char = springs[0];
    auto rest_springs = springs.substr(1);

    if (first_char == '#' || first_char == '?') {
        if (!criteria.empty()) {
            arrangements += get_arrangements(rest_springs, criteria, size + 1);
        }
    }

    if (first_char == '.' || first_char == '?') {
        if (size > 0 && size == criteria[0]) {
            arrangements += get_arrangements(rest_springs, {criteria.begin() + 1, criteria.end()});
        } else if (size == 0) {
            arrangements += get_arrangements(rest_springs, criteria);
        }
    }

    cache[cache_key] = arrangements;
    return arrangements;
}

std::uint64_t part_one(const std::vector<ConditionRecord> &condition_records) {
    std::uint64_t total_arrangements = 0;
    for (const auto &record: condition_records) {
        total_arrangements += get_arrangements(record.springs, record.criteria);
    }

    return total_arrangements;
}

std::uint64_t part_two(const std::vector<ConditionRecord> &condition_records) {
    std::uint64_t total_arrangements = 0;
    for (const auto &record: condition_records) {
        auto springs = record.springs;
        auto criteria = record.criteria;

        auto criteria_size = static_cast<std::uint32_t>(criteria.size());
        auto original_springs = springs;
        for (int i = 0; i < 4; i++) {
            criteria.insert(criteria.end(), criteria.begin(), criteria.begin() + criteria_size);
            springs += "?" + original_springs;
        }

        total_arrangements += get_arrangements(springs, criteria);

        cache.clear();
        cache.reserve(5000);
    }

    return total_arrangements;
}

int main() {
    auto condition_records = parse_file("../../input/2023/day_12/input.txt");

    std::cout << "--- Day 12: Hot Springs ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(condition_records) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(condition_records) << std::endl;
    benchmark::end(start);
}
