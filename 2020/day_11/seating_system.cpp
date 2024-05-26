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
    auto current_layout = std::vector<char>(seat_layout);
    const int height = static_cast<int>(seat_layout.size()) / width;

    while (true) {
        auto next_layout = std::vector<char>(current_layout);
        for (int i = 0; i < current_layout.size(); i++) {
            if (current_layout[i] == '.') continue;
            const int x = i % width;
            const int y = i / width;

            int occupied_seats = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    const int nx = x + dx;
                    const int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        if (current_layout[nx + ny * width] == '#') {
                            occupied_seats++;
                        }
                    }
                }
            }

            if (current_layout[i] == 'L' && occupied_seats == 0) {
                next_layout[i] = '#';
            } else if (current_layout[i] == '#' && occupied_seats >= 4) {
                next_layout[i] = 'L';
            }
        }

        if (current_layout == next_layout) {
            return static_cast<int>(std::count(current_layout.begin(), current_layout.end(), '#'));
        } else {
            std::swap(current_layout, next_layout);
        }
    }
}

int part_two(const std::vector<char> &seat_layout, int width) {
    auto current_layout = std::vector<char>(seat_layout);
    const int height = static_cast<int>(seat_layout.size()) / width;

    while (true) {
        auto next_layout = std::vector<char>(current_layout);
        for (int i = 0; i < current_layout.size(); i++) {
            if (current_layout[i] == '.') continue;
            const int x = i % width;
            const int y = i / width;

            int occupied_seats = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;

                    while (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        if (current_layout[nx + ny * width] == '#') {
                            occupied_seats++;
                            break;
                        } else if (current_layout[nx + ny * width] == 'L') {
                            break;
                        } else {
                            nx += dx;
                            ny += dy;
                        }
                    }
                }
            }

            if (current_layout[i] == 'L' && occupied_seats == 0) {
                next_layout[i] = '#';
            } else if (current_layout[i] == '#' && occupied_seats >= 5) {
                next_layout[i] = 'L';
            }
        }

        if (current_layout == next_layout) {
            return static_cast<int>(std::count(current_layout.begin(), current_layout.end(), '#'));
        } else {
            std::swap(current_layout, next_layout);
        }
    }
}

int main() {
    std::string filename = "../../input/2020/day_11/input.txt";
    auto [seat_layout, width] = parse_file(filename);

    std::cout << "--- Day 11: Seating System ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(seat_layout, width) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(seat_layout, width) << std::endl;
    benchmark::end(start);

    return 0;
}
