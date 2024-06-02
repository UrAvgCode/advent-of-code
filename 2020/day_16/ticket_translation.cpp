// --- Day 16: Ticket Translation ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Rules = std::unordered_map<std::string, std::array<std::array<int, 2>, 2>>;
using Ticket = std::vector<int>;

Ticket parse_ticket(const std::string &line) {
    Ticket ticket;
    std::stringstream stream(line);
    for (std::string token; getline(stream, token, ',');) {
        ticket.push_back(std::stoi(token));
    }
    return ticket;
}

std::tuple<Rules, Ticket, std::vector<Ticket>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    Rules rules;
    for (std::string line; std::getline(file, line) && !line.empty();) {
        auto colon_index = line.find(':');
        auto field_name = line.substr(0, colon_index);

        auto rules_string = line.substr(colon_index + 2);
        auto or_index = rules_string.find("or");

        std::array<std::string, 2> range_strings;
        range_strings[0] = rules_string.substr(0, or_index - 1);
        range_strings[1] = rules_string.substr(or_index + 3);

        std::array<std::array<int, 2>, 2> ranges{};
        for (int i = 0; i < ranges.size(); i++) {
            auto range_string = range_strings[i];
            auto hyphen_index = range_string.find('-');

            int start = std::stoi(range_string.substr(0, hyphen_index));
            int end = std::stoi(range_string.substr(hyphen_index + 1));

            ranges[i] = {start, end};
        }

        rules[field_name] = ranges;
    }

    Ticket my_ticket;
    for (std::string line; std::getline(file, line) && line != "nearby tickets:";) {
        if (std::isdigit(line[0])) {
            my_ticket = parse_ticket(line);
        }
    }

    std::vector<Ticket> tickets;
    for (std::string line; std::getline(file, line);) {
        tickets.emplace_back(parse_ticket(line));
    }

    return {rules, my_ticket, tickets};
}

int part_one(const Rules &rules, const std::vector<Ticket> &tickets) {
    std::vector<int> invalid_values;
    for (auto &ticket: tickets) {
        for (auto &value: ticket) {
            bool is_valid_value = false;

            for (auto &[_, rule]: rules) {
                for (auto &[start, end]: rule) {
                    if (value >= start && value <= end) {
                        is_valid_value = true;
                    }
                }
            }

            if (!is_valid_value) {
                invalid_values.push_back(value);
            }
        }
    }

    return std::accumulate(invalid_values.begin(), invalid_values.end(), 0);
}

std::uint64_t part_two(const Rules &rules, const Ticket &my_ticket, const std::vector<Ticket> &tickets) {
    std::vector<Ticket> valid_tickets;
    for (auto &ticket: tickets) {
        bool is_valid_ticket = true;

        for (auto &value: ticket) {
            bool is_valid_value = false;

            for (auto &[_, rule]: rules) {
                for (auto &[start, end]: rule) {
                    if (value >= start && value <= end) {
                        is_valid_value = true;
                    }
                }
            }

            if (!is_valid_value) {
                is_valid_ticket = false;
                break;
            }
        }

        if(is_valid_ticket) {
            valid_tickets.push_back(ticket);
        }
    }

    std::vector<std::unordered_set<std::string>> possible_orders(valid_tickets[0].size());
    for(auto &possible_fields : possible_orders) {
        for(auto &[field_name, _]: rules) {
            possible_fields.insert(field_name);
        }
    }

    for(auto &ticket: valid_tickets) {
        for(int i = 0; i < ticket.size(); i++) {
            auto value = ticket[i];
            for(auto &[field_name, rule]: rules) {
                bool is_possible_field = false;

                for (auto &[start, end]: rule) {
                    if (value >= start && value <= end) {
                        is_possible_field = true;
                    }
                }

                if(!is_possible_field) {
                    possible_orders[i].erase(field_name);
                }
            }
        }
    }

    bool multiple_possibilities = true;
    while (multiple_possibilities) {
        multiple_possibilities = false;
        for(auto &possible_fields : possible_orders) {
            if(possible_fields.size() > 1) {
                multiple_possibilities = true;
            } else {
                for(auto &other_fields : possible_orders) {
                    if(other_fields != possible_fields) {
                        other_fields.erase(*possible_fields.begin());
                    }
                }
            }
        }

    }

    std::uint64_t result = 1;
    for(int i = 0; i < my_ticket.size(); i++) {
        if((*possible_orders[i].begin()).starts_with("departure")) {
            result *= my_ticket[i];
        }
    }

    return result;
}

int main() {
    std::string filename = "../../input/2020/day_16/input.txt";
    auto [rules, my_ticket, tickets] = parse_file(filename);

    std::cout << "--- Day 16: Ticket Translation ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(rules, tickets) << std::endl;
    benchmark::end(start);

    start = benchmark::start();
    std::cout << "\nPart 2: " << part_two(rules, my_ticket, tickets) << std::endl;
    benchmark::end(start);

    return 0;
}
