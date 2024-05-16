// --- Day 12: Hot Springs ---

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <chrono>
#include <cstdint>
#include <sstream>
#include <cmath>

struct condition_record {
    std::string springs;
    std::vector<std::uint8_t> criteria;
};

std::vector<condition_record> parse_file(const std::string &filename) {
    auto records = std::vector<condition_record>();
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

            records.push_back(condition_record{springs, criteria});
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return records;
}

std::unordered_map<std::string, std::uint64_t> cache;
std::uint64_t get_arrangements(condition_record record, std::uint8_t size = 0) {
    std::uint64_t arrangements = 0;
    auto springs = record.springs;
    auto criteria = record.criteria;

    if (springs.empty()) {
        if (criteria.empty() || (criteria.size() == 1 && criteria[0] == size)) {
            return 1;
        } else {
            return 0;
        }
    }

    auto lookup_string = springs;
    for (const auto &num: criteria) {
        lookup_string += std::to_string(num) + ",";
    }

    lookup_string += " " + std::to_string(size);

    auto it = cache.find(lookup_string);
    if (it == cache.end()) {

        auto c = springs[0];
        if (c == '#' || c == '?') {
            if (!criteria.empty()) {
                arrangements += get_arrangements(condition_record{springs.substr(1), criteria}, size + 1);
            }
        }

        if (c == '.' || c == '?') {
            if (0 < size && size == criteria[0]) {
                auto new_criteria = std::vector<std::uint8_t>(criteria.size() - 1);
                for (std::uint32_t i = 1; i < criteria.size(); i++) {
                    new_criteria[i - 1] = criteria[i];
                }
                arrangements += get_arrangements(condition_record{springs.substr(1), new_criteria});
            } else if (size == 0) {
                arrangements += get_arrangements(condition_record{springs.substr(1), criteria});
            }
        }

        cache[lookup_string] = arrangements;
    } else {
        arrangements += it->second;
    }

    return arrangements;
}


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto condition_records = parse_file("2023/day_12/hot_springs_input");

    std::uint64_t total_arrangements = 0;
    for (const auto &record: condition_records) {
        total_arrangements += get_arrangements(record);
    }

    std::cout << "Part 1: " << total_arrangements << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    auto seconds = static_cast<std::double_t>(duration.count()) / 1'000'000'000.0;
    std::cout << "Time: " << seconds << "s" << std::endl;
}
