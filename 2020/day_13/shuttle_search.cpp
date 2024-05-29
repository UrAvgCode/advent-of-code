// --- Day 13: Shuttle Search ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

std::pair<int, std::map<int, int>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::string line;
    getline(file, line);
    int earliest_timestamp = std::stoi(line);

    getline(file, line);
    std::stringstream stream(line);

    int number = 0;
    std::map<int, int> buses;
    for (std::string token; getline(stream, token, ',');) {
        if (token != "x") {
            buses[number] = std::stoi(token);
        }
        number++;
    }

    return {earliest_timestamp, buses};
}

int part_one(const int earliest_timestamp, const std::map<int, int> &buses) {
    auto wait_times = std::map<int, int>();
    for (const auto &[_, bus_id]: buses) {
        wait_times[bus_id - (earliest_timestamp % bus_id)] = bus_id;
    }

    auto &[wait_time, bus_id] = *wait_times.begin();
    return wait_time * bus_id;
}

std::uint64_t part_two(const std::map<int, int> &buses) {
    std::uint64_t earliest_timestamp = buses.at(0);
    std::uint64_t step_size = 1;

    for (const auto &[number, id]: buses) {
        while ((earliest_timestamp + number) % id != 0) {
            earliest_timestamp += step_size;
        }
        step_size *= id;
    }

    return earliest_timestamp;
}

int main() {
    std::string filename = "../../input/2020/day_13/input.txt";
    auto [earliest_timestamp, buses] = parse_file(filename);

    std::cout << "--- Day 13: Shuttle Search ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(earliest_timestamp, buses) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(buses) << std::endl;
    benchmark::end(start);

    return 0;
}
