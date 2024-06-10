#pragma once

#include "benchmark.h"

#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Solver {
private:
    const int _year;
    const int _day;
    const std::string _name;

    int current_part = 1;

public:
    Solver(const int year, const int day, const std::string &name) : _year(year), _day(day), _name(name) {
        std::cout << "--- Day " << day << ": " << name << " ---" << std::endl;
    }

    template<typename Func, typename... Args>
    void operator()(Func func, Args... args) {
        auto start = benchmark::start();
        std::cout << "\nPart " << current_part++ << ": " << func(args...) << std::endl;
        benchmark::end(start);
    }

    template<typename Func>
    auto parse_file(Func parser) {
        std::stringstream stream;
        stream << "../../input/" << _year << "/day_" << std::setw(2) << std::setfill('0') << _day << "/input.txt";

        std::string filename = stream.str();
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("unable to open file: " + filename);
        }

        return parser(file);
    }
};
