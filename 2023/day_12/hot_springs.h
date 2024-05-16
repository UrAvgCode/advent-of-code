#pragma once

#include <cmath>
#include <cstdint>
#include <numeric>
#include <string>
#include <vector>
#include <tuple>

struct ConditionRecord {
    std::string springs;
    std::vector<std::uint8_t> criteria;
    std::uint8_t size = 0;

    bool operator==(const ConditionRecord &other) const {
        return springs == other.springs && size == other.size && criteria == other.criteria;
    }
};

namespace std {
    template<>
    struct hash<ConditionRecord> {
        size_t operator()(const ConditionRecord &key) const {
            std::size_t h1 = std::hash<std::string>{}(key.springs);
            std::size_t h2 = std::hash<std::uint8_t>{}(key.size);
            std::size_t h3 = 0;
            for (auto num: key.criteria) {
                h3 = h3 * 31 + std::hash<std::uint8_t>{}(num);
            }
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}