// --- Day 17: Conway Cubes ---

#pragma once

#include <vector>

struct Cube {
private:
    std::vector<char> _data;
    std::size_t _width;
    std::size_t _height;
    std::size_t _depth;

public:
    Cube(std::size_t width, std::size_t height, std::size_t depth) : _width(width), _height(height), _depth(depth) {
        _data = std::vector<char>(width * height * depth, '.');
    }

    char get(int x, int y, int z) {
        if (x < 0 || x >= _width || y < 0 || y >= _height || z < 0 || z >= _depth) {
            return '.';
        } else {
            return _data[x + (_width * y) + (_width * _height * z)];
        }
    }

    void set(int x, int y, int z, char value) { _data[x + (_width * y) + (_width * _height * z)] = value; }

    [[nodiscard]] std::size_t width() const { return _width; }

    [[nodiscard]] std::size_t height() const { return _height; }

    [[nodiscard]] std::size_t depth() const { return _depth; }

    [[nodiscard]] std::size_t size() const { return _data.size(); }

    [[nodiscard]] std::vector<char> data() const { return _data; }
};
