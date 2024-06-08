// --- Day 12: Hot Springs ---

#pragma once

#include <cstdint>
#include <string>
#include <vector>

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
            std::size_t h3 = std::hash<std::string>{}({key.criteria.begin(), key.criteria.end()});
            return h1 ^ h2 ^ h3;
        }
    };
} // namespace std
