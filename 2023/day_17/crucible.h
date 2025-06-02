#pragma once

#include <cstdint>
#include <functional>

namespace clumsy_crucible {
    struct crucible {
        std::uint8_t x;
        std::uint8_t y;
        std::int8_t dx;
        std::int8_t dy;
        std::uint16_t speed;
        std::uint16_t heat_loss;

        bool operator==(const crucible &) const;

        bool operator>(const crucible &) const noexcept;

        bool operator<(const crucible &) const noexcept;
    };
} // namespace clumsy_crucible

template<>
struct std::hash<clumsy_crucible::crucible> {
    std::size_t operator()(const clumsy_crucible::crucible &) const noexcept;
};
