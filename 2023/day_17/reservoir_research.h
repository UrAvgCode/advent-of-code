// --- Day 17: Reservoir Research ---

# pragma once

#include <array>
#include <string>
#include <cstdint>

struct Crucible {
    int x;
    int y;
    int x_dir;
    int y_dir;
    int speed;
    int heat_loss;

    bool operator==(const Crucible &other) const {
        return x == other.x && y == other.y && x_dir == other.x_dir && y_dir == other.y_dir && speed == other.speed;
    }

    bool operator>(const Crucible &other) const {
        return heat_loss > other.heat_loss;
    }

    bool operator<(const Crucible &other) const {
        return heat_loss < other.heat_loss;
    }
};

namespace std {
    template<>
    struct hash<Crucible> {
        std::size_t operator()(const Crucible &crucible) const {
            std::size_t hash_1 = std::hash<int>{}(crucible.x);
            std::size_t hash_2 = std::hash<int>{}(crucible.y);
            std::size_t hash_3 = std::hash<int>{}(crucible.x_dir);
            std::size_t hash_4 = std::hash<int>{}(crucible.y_dir);
            std::size_t hash_5 = std::hash<int>{}(crucible.speed);

            return hash_1 ^ (hash_2 << 1) ^ (hash_3 << 2) ^ (hash_4 << 3) ^ (hash_5 << 4);
        }
    };
}