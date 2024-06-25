// --- Day 12: Hot Springs ---

#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct ConditionRecord {
    std::string springs;
    std::vector<std::uint8_t> criteria;
    std::uint8_t size = 0;

    bool operator==(const ConditionRecord &other) const noexcept {
        return springs == other.springs && size == other.size && criteria == other.criteria;
    }
};

template<>
struct std::hash<ConditionRecord> {
    size_t operator()(const ConditionRecord &key) const noexcept {
        const auto hash_one = std::hash<std::string>{}(key.springs);
        const auto hash_two = std::hash<std::uint8_t>{}(key.size);
        const auto hash_three = std::hash<std::string>{}({key.criteria.begin(), key.criteria.end()});
        return hash_one ^ hash_two ^ hash_three;
    }
};
