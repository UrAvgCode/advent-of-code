// --- Day 12: Hot Springs ---

#pragma once

#include <cstdint>
#include <span>
#include <string>

struct ConditionRecord {
    const std::span<const char> springs;
    const std::span<const std::uint8_t> criteria;
    const std::uint8_t size = 0;

    bool operator==(const ConditionRecord &other) const noexcept {
        return springs.size() == other.springs.size() && criteria.size() == other.criteria.size() &&
               size == other.size && std::equal(springs.begin(), springs.end(), other.springs.begin()) &&
               std::equal(criteria.begin(), criteria.end(), other.criteria.begin());
    }
};

template<>
struct std::hash<ConditionRecord> {
    size_t operator()(const ConditionRecord &key) const noexcept {
        const auto hash_one = std::hash<std::string>{}({key.springs.begin(), key.springs.end()});
        const auto hash_two = std::hash<std::string>{}({key.criteria.begin(), key.criteria.end()});
        const auto hash_three = std::hash<std::uint8_t>{}(key.size);
        return hash_one ^ hash_two ^ hash_three;
    }
};
