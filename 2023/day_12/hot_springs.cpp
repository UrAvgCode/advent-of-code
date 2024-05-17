// --- Day 12: Hot Springs ---

#include "hot_springs.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>

std::vector<ConditionRecord> parse_file(const std::string &filename) {
    auto records = std::vector<ConditionRecord>();
    records.reserve(1000);

    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            auto index = line.find(' ');
            auto springs = line.substr(0, index);

            auto criteria = std::vector<std::uint8_t>();
            auto stream = std::stringstream(line.substr(index + 1));

            std::string temp;
            while (getline(stream, temp, ',')) {
                criteria.push_back(stoi(temp));
            }

            records.push_back(ConditionRecord{springs, criteria});
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
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

int main() {
    auto condition_records = parse_file("input/2023/day_12/input.txt");

    {
        auto start = std::chrono::high_resolution_clock::now();

        std::uint64_t total_arrangements = 0;
        for (const auto &record: condition_records) {
            total_arrangements += get_arrangements(record.springs, record.criteria);
        }

        std::cout << "Part 1: " << total_arrangements << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        auto seconds = static_cast<std::double_t>(duration.count()) / 1'000'000'000.0;
        std::cout << "Time: " << seconds << "s" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();

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

        std::cout << "\nPart 2: " << total_arrangements << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        auto seconds = static_cast<std::double_t>(duration.count()) / 1'000'000'000.0;
        std::cout << "Time: " << seconds << "s" << std::endl;
    }
}
