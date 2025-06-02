#include "crucible.h"

#include <bit>

bool clumsy_crucible::crucible::operator==(const crucible &other) const {
    return x == other.x && y == other.y && dx == other.dx && dy == other.dy && speed == other.speed;
}

bool clumsy_crucible::crucible::operator>(const crucible &other) const noexcept { return heat_loss > other.heat_loss; }

bool clumsy_crucible::crucible::operator<(const crucible &other) const noexcept { return heat_loss < other.heat_loss; }

std::size_t std::hash<clumsy_crucible::crucible>::operator()(const clumsy_crucible::crucible &key) const noexcept {
    static_assert(sizeof(key) == sizeof(std::size_t));

    constexpr auto heat_loss_offset = offsetof(clumsy_crucible::crucible, heat_loss);
    constexpr auto heat_loss_size = sizeof(key.heat_loss);
    constexpr auto heat_loss_mask = ~(((1ull << (heat_loss_size * 8)) - 1) << (heat_loss_offset * 8));

    return std::bit_cast<std::size_t>(key) & heat_loss_mask;
}
