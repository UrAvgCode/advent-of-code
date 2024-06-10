// --- Day 13: Shuttle Search ---

#include "solver.h"

#include <fstream>
#include <map>
#include <ranges>
#include <string>

std::pair<int, std::map<int, int>> parser(std::ifstream &file) {
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
    for (const auto &bus_id: std::views::values(buses)) {
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
    Solver solver(2020, 13, "Shuttle Search");

    auto [earliest_timestamp, buses] = solver.parse_file(parser);
    solver(part_one, earliest_timestamp, buses);
    solver(part_two, buses);

    return 0;
}
