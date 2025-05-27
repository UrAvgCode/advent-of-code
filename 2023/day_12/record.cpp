#include "record.h"

#include <string_view>

bool hot_springs::record::operator==(const record &other) const noexcept {
    if (size != other.size || springs.size() != other.springs.size() || criteria.size() != other.criteria.size()) {
        return false;
    }

    return std::equal(springs.begin(), springs.end(), other.springs.begin()) &&
           std::equal(criteria.begin(), criteria.end(), other.criteria.begin());
}

std::size_t std::hash<hot_springs::record>::operator()(const hot_springs::record &key) const noexcept {
    const auto &[springs, criteria, size] = key;

    const auto springs_view = std::string_view(reinterpret_cast<const char *>(springs.data()), springs.size());
    const auto criteria_view = std::string_view(reinterpret_cast<const char *>(criteria.data()), criteria.size());

    const auto hash_one = std::hash<std::string_view>{}(springs_view);
    const auto hash_two = std::hash<std::string_view>{}(criteria_view);
    const auto hash_three = std::hash<std::uint8_t>{}(size);

    return hash_one ^ hash_two ^ hash_three;
}
