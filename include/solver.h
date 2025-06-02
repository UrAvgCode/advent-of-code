#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <print>
#include <sstream>

class Solver {
public:
    Solver(const int year, const int day, const char *name) : _year(year), _day(day), _name(name) {
        std::println("--- Day {}: {} ---", day, name);
    }

    template<typename Func, typename... Args>
    void operator()(Func func, Args... args) {
        const auto start = std::chrono::high_resolution_clock::now();

        std::println("\nPart {}: {}", _current_part++, func(args...));

        const auto end = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        auto output = static_cast<double>(duration.count());

        const char *unit;
        if (output >= 100'000'000) {
            output /= 1'000'000'000;
            unit = "s";
        } else if (output >= 1'000) {
            output /= 1'000'000;
            unit = "ms";
        } else {
            output /= 1'000;
            unit = "us";
        }

        std::println("Time: {}{}", output, unit);
    }

    template<typename Func>
    auto parse_file(Func parser) {
        auto stream = std::stringstream();
        stream << "../../input/" << _year << "/day_" << std::setw(2) << std::setfill('0') << _day << "/input.txt";

        const auto filename = stream.str();
        auto file = std::ifstream(filename);
        if (!file) {
            throw std::runtime_error("unable to open file: " + filename);
        }

        return parser(file);
    }

private:
    const int _year;
    const int _day;
    const char *_name;

    int _current_part = 1;
};
