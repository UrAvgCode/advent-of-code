// --- Day 16: Ticket Translation ---

#include "solver.h"

#include <fstream>
#include <numeric>
#include <ranges>
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

std::tuple<Rules, Ticket, std::vector<Ticket>> parser(std::ifstream &file) {
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
    for (const auto &ticket: tickets) {
        for (const auto &value: ticket) {
            if (!std::any_of(rules.begin(), rules.end(), [&](const auto &rule) {
                return std::any_of(rule.second.begin(), rule.second.end(), [&](const auto &range) {
                    return value >= range[0] && value <= range[1];
                });
            })) {
                invalid_values.push_back(value);
            }
        }
    }

    return std::reduce(invalid_values.begin(), invalid_values.end());
}

std::uint64_t part_two(const Rules &rules, const Ticket &my_ticket, const std::vector<Ticket> &tickets) {
    std::vector<Ticket> valid_tickets;
    for (const auto &ticket: tickets) {
        if (std::all_of(ticket.begin(), ticket.end(), [&](int value) {
            return std::any_of(rules.begin(), rules.end(), [&](const auto &rule) {
                return std::any_of(rule.second.begin(), rule.second.end(), [&](const auto &range) {
                    return value >= range[0] && value <= range[1];
                });
            });
        })) {
            valid_tickets.emplace_back(ticket);
        }
    }

    std::vector<std::unordered_set<std::string>> correct_order(rules.size());
    for (auto &possible_fields: correct_order) {
        for (const auto &field_name: std::views::keys(rules)) {
            possible_fields.insert(field_name);
        }
    }

    for (const auto &ticket: valid_tickets) {
        for (std::size_t i = 0; i < ticket.size(); i++) {
            const auto value = ticket[i];
            for (const auto &[field_name, rule]: rules) {
                if (!std::any_of(rule.begin(), rule.end(), [&](const auto &range) {
                    return value >= range[0] && value <= range[1];
                })) {
                    correct_order[i].erase(field_name);
                }
            }
        }
    }

    while (std::any_of(correct_order.begin(), correct_order.end(), [](auto &possible_fields) {
        return possible_fields.size() > 1;
    })) {
        for (auto &possible_fields: correct_order) {
            if (possible_fields.size() == 1) {
                for (auto &other_fields: correct_order) {
                    if (other_fields != possible_fields) {
                        other_fields.erase(*possible_fields.begin());
                    }
                }
            }
        }
    }

    std::uint64_t result = 1;
    for (std::size_t i = 0; i < my_ticket.size(); i++) {
        auto field_name = (*correct_order[i].begin());
        if (field_name.starts_with("departure")) {
            result *= my_ticket[i];
        }
    }

    return result;
}

int main() {
    Solver solver(2020, 16, "Ticket Translation");

    auto [rules, my_ticket, tickets] = solver.parse_file(parser);
    solver(part_one, rules, tickets);
    solver(part_two, rules, my_ticket, tickets);

    return 0;
}
