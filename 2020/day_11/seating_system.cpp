// --- Day 11: Seating System ---

#include "benchmark.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::pair<std::vector<char>, int> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    int width = 0;
    std::vector<char> seat_layout;
    for (std::string line; getline(file, line);) {
        if (width == 0) width = static_cast<int>(line.size());
        seat_layout.insert(seat_layout.end(), line.begin(), line.end());
    }

    return {seat_layout, width};
}

int part_one(const std::vector<char> &seat_layout, int width) {
    auto current_layout = std::vector<char>(seat_layout.begin(), seat_layout.end());
    int height = static_cast<int>(seat_layout.size()) / width;

    bool changed = true;
    while (changed) {
        changed = false;
        auto new_layout = std::vector<char>(current_layout.begin(), current_layout.end());

        for (int i = 0; i < current_layout.size(); i++) {
            if (current_layout[i] == '.') continue;
            int x = i % width;
            int y = i / width;

            int adjacent = 0;
            for(int dx = -1; dx <= 1; dx++) {
                for(int dy = -1; dy <= 1; dy++) {
                    if(dx == 0 && dy == 0) continue;

                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        if(current_layout[nx + ny * width] == '#') {
                            adjacent++;
                        }
                    }
                }
            }

            if(current_layout[i] == 'L' && adjacent == 0) {
                changed = true;
                new_layout[i] = '#';
            } else if(current_layout[i] == '#' && adjacent >= 4) {
                changed = true;
                new_layout[i] = 'L';
            }
        }

        current_layout = new_layout;
    }

    return static_cast<int>(std::count(current_layout.begin(), current_layout.end(), '#'));
}

int main() {
    std::string filename = "../../input/2020/day_11/input.txt";
    auto [seat_layout, width] = parse_file(filename);

    std::cout << "--- Day 11: Seating System ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(seat_layout, width) << std::endl;
    benchmark::end(start);

    return 0;
}
