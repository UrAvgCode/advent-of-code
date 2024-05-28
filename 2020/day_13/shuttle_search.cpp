// --- Day 13: Shuttle Search ---

#include "benchmark.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::pair<int, std::vector<int>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::string line;
    getline(file, line);
    int earliest_timestamp = std::stoi(line);

    getline(file, line);
    std::stringstream stream(line);
    std::vector<int> bus_ids;
    for (std::string token; getline(stream, token, ',');) {
        if (token == "x") {
            bus_ids.push_back(-1);
        } else {
            bus_ids.push_back(std::stoi(token));
        }
    }

    return {earliest_timestamp, bus_ids};
}

int part_one(const int earliest_timestamp, const std::vector<int> &bus_ids) {
    auto wait_times = std::vector<int>(bus_ids.size(), std::numeric_limits<int>::max());
    for (int i = 0; i < bus_ids.size(); i++) {
        auto id = bus_ids[i];
        if (id == -1) continue;
        wait_times[i] = id - (earliest_timestamp % id);
    }

    auto min_element = std::min_element(wait_times.begin(), wait_times.end());
    auto index = std::distance(wait_times.begin(), min_element);

    return bus_ids[index] * wait_times[index];
}

std::uint64_t part_two(const std::vector<int> &bus_ids) {
    std::uint64_t earliest_timestamp = 0;
    auto step_size = static_cast<std::uint64_t>(bus_ids[0]);

    for(int i = 1; i < bus_ids.size(); i++) {
        if(bus_ids[i] == -1) continue;
        while ((earliest_timestamp + i) % bus_ids[i] != 0) {
            earliest_timestamp += step_size;
        }
        step_size *= bus_ids[i];
    }

    return earliest_timestamp;
}

int main() {
    std::string filename = "../../input/2020/day_13/input.txt";
    auto [earliest_timestamp, bus_ids] = parse_file(filename);

    std::cout << "--- Day 13: Shuttle Search ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(earliest_timestamp, bus_ids) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(bus_ids) << std::endl;
    benchmark::end(start);

    return 0;
}
