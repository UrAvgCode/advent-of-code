#pragma once

#include <cstdint>
#include <functional>
#include <span>

namespace hot_springs {
    struct record {
        const std::span<const std::uint8_t> springs;
        const std::span<const std::uint8_t> criteria;
        const std::uint8_t size = 0;

        bool operator==(const record &) const noexcept;
    };
} // namespace hot_springs

template<>
struct std::hash<hot_springs::record> {
    std::size_t operator()(const hot_springs::record &) const noexcept;
};
