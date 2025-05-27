// --- Day 12: Hot Springs ---

#include "record.h"
#include "solver.h"

#include <execution>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>

#ifdef PARALLEL
constexpr auto policy = std::execution::par;
#else
constexpr auto policy = std::execution::seq;
#endif

using cache_t = std::unordered_map<hot_springs::record, std::uint64_t>;

std::vector<hot_springs::record> parser(std::ifstream &file) {
    static auto springs_data = std::vector<std::uint8_t>();
    static auto criteria_data = std::vector<std::uint8_t>();
    auto spring_indices = std::vector<std::size_t>({0});
    auto criteria_indices = std::vector<std::size_t>({0});

    for (std::string line; getline(file, line);) {
        const auto space_index = static_cast<std::ptrdiff_t>(line.find(' '));
        springs_data.insert(springs_data.end(), line.begin(), line.begin() + space_index);
        spring_indices.emplace_back(springs_data.size());

        auto criteria_stream = std::stringstream(line.substr(space_index + 1));
        for (std::string temp; getline(criteria_stream, temp, ',');) {
            criteria_data.emplace_back(stoi(temp));
        }

        criteria_indices.emplace_back(criteria_data.size());
    }

    auto records = std::vector<hot_springs::record>();
    for (std::size_t i = 0; i < spring_indices.size() - 1; ++i) {
        const auto spring_begin = springs_data.data() + spring_indices[i];
        const auto spring_size = spring_indices[i + 1] - spring_indices[i];

        const auto criteria_begin = criteria_data.data() + criteria_indices[i];
        const auto criteria_size = criteria_indices[i + 1] - criteria_indices[i];

        records.emplace_back(std::span(spring_begin, spring_size), std::span(criteria_begin, criteria_size));
    }

    return records;
}

std::uint64_t get_arrangements(const hot_springs::record &record, cache_t &cache) {
    const auto &[springs, criteria, size] = record;

    if (springs.empty()) {
        return criteria.empty() || (criteria.size() == 1 && criteria[0] == size);
    }

    const auto cache_key = hot_springs::record{springs, criteria, size};
    if (cache.contains(cache_key)) {
        return cache[cache_key];
    }

    std::uint64_t arrangements = 0;
    const auto current_spring = springs.front();
    const auto remaining_springs = springs.subspan(1);

    if (current_spring == '#' || current_spring == '?') {
        if (!criteria.empty()) {
            const auto next_size = static_cast<std::uint8_t>(size + 1);
            arrangements += get_arrangements({remaining_springs, criteria, next_size}, cache);
        }
    }

    if (current_spring == '.' || current_spring == '?') {
        if (size > 0 && size == criteria[0]) {
            arrangements += get_arrangements({remaining_springs, {criteria.begin() + 1, criteria.end()}, 0}, cache);
        } else if (size == 0) {
            arrangements += get_arrangements({remaining_springs, criteria, 0}, cache);
        }
    }

    cache[cache_key] = arrangements;
    return arrangements;
}

std::uint64_t part_one(const std::vector<hot_springs::record> &records) {
    return std::transform_reduce(policy, records.begin(), records.end(), 0ull, std::plus(), [](const auto &record) {
        auto cache = cache_t(1ull << 10ull);
        return get_arrangements(record, cache);
    });
}

std::uint64_t part_two(const std::vector<hot_springs::record> &records) {
    return std::transform_reduce(policy, records.begin(), records.end(), 0ull, std::plus(), [](const auto &record) {
        const auto &[springs, criteria, size] = record;

        auto expanded_springs = std::vector<std::uint8_t>();
        auto expanded_criteria = std::vector<std::uint8_t>();
        expanded_springs.reserve(springs.size() * 5 + 4);
        expanded_criteria.reserve(criteria.size() * 5);

        for (std::size_t i = 0; i < 5; ++i) {
            if (i > 0) {
                expanded_springs.push_back('?');
            }
            expanded_springs.insert(expanded_springs.end(), springs.begin(), springs.end());
            expanded_criteria.insert(expanded_criteria.end(), criteria.begin(), criteria.end());
        }

        auto cache = cache_t(1ull << 15ull);
        return get_arrangements({expanded_springs, expanded_criteria}, cache);
    });
}

int main() {
    Solver solver(2023, 12, "Hot Springs");

    const auto condition_records = solver.parse_file(parser);
    solver(part_one, condition_records);
    solver(part_two, condition_records);

    return 0;
}
