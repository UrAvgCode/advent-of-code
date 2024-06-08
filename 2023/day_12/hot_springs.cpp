// --- Day 12: Hot Springs ---

#include "hot_springs.h"
#include "benchmark.h"

#include <execution>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>

#ifdef PARALLEL
auto policy = std::execution::par;
#else
auto policy = std::execution::seq;
#endif

std::vector<ConditionRecord> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<ConditionRecord> records;
    for (std::string line; getline(file, line);) {
        auto space_pos = line.find(' ');
        auto springs = line.substr(0, space_pos);

        auto criteria = std::vector<std::uint8_t>();
        auto criteria_stream = std::stringstream(line.substr(space_pos + 1));
        for (std::string temp; getline(criteria_stream, temp, ',');) {
            criteria.push_back(stoi(temp));
        }

        records.emplace_back(springs, criteria);
    }

    return records;
}

std::uint64_t get_arrangements(const ConditionRecord &record) {
    std::unordered_map<ConditionRecord, std::uint64_t> cache(4096);
    std::function<std::uint64_t(const std::string &, const std::vector<std::uint8_t> &, const std::uint8_t)>
            recursive_lambda;
    recursive_lambda = [&cache, &recursive_lambda](const std::string &springs,
                                                   const std::vector<std::uint8_t> &criteria,
                                                   const std::uint8_t size) -> std::uint64_t {
        if (springs.empty()) {
            return criteria.empty() || (criteria.size() == 1 && criteria[0] == size);
        }

        auto cache_key = ConditionRecord{springs, criteria, size};
        if (cache.contains(cache_key)) {
            return cache[cache_key];
        }

        std::uint64_t arrangements = 0;
        char first_char = springs[0];
        auto rest_springs = springs.substr(1);

        if (first_char == '#' || first_char == '?') {
            if (!criteria.empty()) {
                arrangements += recursive_lambda(rest_springs, criteria, size + 1);
            }
        }

        if (first_char == '.' || first_char == '?') {
            if (size > 0 && size == criteria[0]) {
                arrangements += recursive_lambda(rest_springs, {criteria.begin() + 1, criteria.end()}, 0);
            } else if (size == 0) {
                arrangements += recursive_lambda(rest_springs, criteria, 0);
            }
        }

        cache[cache_key] = arrangements;
        return arrangements;
    };

    return recursive_lambda(record.springs, record.criteria, 0);
}

std::uint64_t part_one(const std::vector<ConditionRecord> &condition_records) {
    return std::transform_reduce(policy, condition_records.begin(), condition_records.end(), 0ull, std::plus<>(),
                                 get_arrangements);
}

std::uint64_t part_two(const std::vector<ConditionRecord> &condition_records) {
    return std::transform_reduce(
            policy, condition_records.begin(), condition_records.end(), 0ull, std::plus<>(), [](const auto &record) {
                auto springs = record.springs;
                auto criteria = record.criteria;
                auto criteria_size = criteria.size();

                for (int i = 0; i < 4; i++) {
                    criteria.insert(criteria.end(), criteria.begin(), criteria.begin() + criteria_size);
                    springs += "?" + record.springs;
                }

                return get_arrangements({springs, criteria});
            });
}

int main() {
    std::string filename = "../../input/2023/day_12/input.txt";
    auto condition_records = parse_file(filename);

    std::cout << "--- Day 12: Hot Springs ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(condition_records) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(condition_records) << std::endl;
    benchmark::end(start);
}
