#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <print>
#include <utility>

class Solver {
public:
    Solver(const int year, const int day, const char *name) : _year(year), _day(day), _name(name) {
        std::println("--- Day {}: {} ---", day, name);
    }

    template<typename Func, typename... Args>
    void operator()(Func &&func, Args &&...args) {
        const auto start = std::chrono::high_resolution_clock::now();

        const auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

        const auto end = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        auto output = static_cast<double>(duration.count());

        const char *unit;
        if (output >= 1'000'000'000) {
            output /= 1'000'000'000;
            unit = "s";
        } else if (output >= 1'000'000) {
            output /= 1'000'000;
            unit = "ms";
        } else if (output >= 1'000) {
            output /= 1'000;
            unit = "μs";
        } else {
            unit = "ns";
        }

        std::println("\nPart {}: {}", _current_part++, result);
        std::println("Time: {:.3f}{}", output, unit);
    }

    template<typename Func>
    auto parse_file(Func &&parser) {
        const auto filename = std::format("../../input/{}/day_{:02d}/input.txt", _year, _day);
        auto file = std::ifstream(filename);
        if (!file.is_open()) {
            throw std::runtime_error(std::format("unable to open file: {}", filename));
        }

        return std::invoke(std::forward<Func>(parser), file);
    }

private:
    const int _year;
    const int _day;
    const char *_name;

    int _current_part = 1;
};
