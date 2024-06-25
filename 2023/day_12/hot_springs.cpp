// --- Day 12: Hot Springs ---

#include "hot_springs.h"
#include "solver.h"

#include <execution>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>

#ifdef PARALLEL
auto policy = std::execution::par;
#else
auto policy = std::execution::seq;
#endif

std::vector<ConditionRecord> parser(std::ifstream &file) {
    std::vector<ConditionRecord> records;
    for (std::string line; getline(file, line);) {
        const auto space_pos = line.find(' ');
        auto springs = line.substr(0, space_pos);

        std::vector<std::uint8_t> criteria;
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

        const auto cache_key = ConditionRecord{springs, criteria, size};
        if (cache.contains(cache_key)) {
            return cache[cache_key];
        }

        std::uint64_t arrangements = 0;
        const char first_char = springs[0];
        const auto rest_springs = springs.substr(1);

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
    Solver solver(2023, 12, "Hot Springs");

    const auto condition_records = solver.parse_file(parser);
    solver(part_one, condition_records);
    solver(part_two, condition_records);

    return 0;
}
