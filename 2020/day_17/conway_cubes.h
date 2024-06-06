// --- Day 17: Conway Cubes ---

#pragma once

#include <algorithm>
#include <vector>

template<std::size_t N>
class Hypercube {
private:
    std::vector<char> _data;
    std::array<std::size_t, N> _dimensions;

public:
    explicit Hypercube(const std::array<std::size_t, N> &dimensions) : _dimensions(dimensions) {
        std::size_t size = 1;
        for (auto dim: _dimensions) {
            size *= dim;
        }
        _data = std::vector<char>(size, '.');
    }

    char get(const std::array<int, N> &coords) {
        std::size_t index = 0;
        std::size_t stride = 1;
        for (std::size_t i = 0; i < N; ++i) {
            if (coords[i] < 0 || static_cast<std::size_t>(coords[i]) >= _dimensions[i]) {
                return '.';
            }
            index += coords[i] * stride;
            stride *= _dimensions[i];
        }
        return _data[index];
    }

    void set(const std::array<int, N> &coords, char value) {
        std::size_t index = 0;
        std::size_t stride = 1;
        for (std::size_t i = 0; i < N; ++i) {
            index += coords[i] * stride;
            stride *= _dimensions[i];
        }
        _data[index] = value;
    }

    [[nodiscard]] std::size_t size() const { return _data.size(); }

    [[nodiscard]] std::size_t size(std::size_t n) const { return _dimensions[n]; }

    [[nodiscard]] std::vector<char> data() const { return _data; }
};
