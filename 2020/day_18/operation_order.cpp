// --- Day 18: Operation Order ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <stack>
#include <string>

std::vector<std::string> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<std::string> expressions;
    for (std::string line; std::getline(file, line);) {
        expressions.push_back(line);
    }

    return expressions;
}

std::uint64_t part_one(const std::vector<std::string> &expressions) {
    std::uint64_t sum = 0;
    for (const auto &expression: expressions) {
        std::stack<std::uint64_t> operand_stack;
        std::stack<char> operator_stack;

        for (char op: expression) {
            if (op == ' ') {
                continue;

            } else if (isdigit(op)) {
                int operand = op - '0';
                if (operator_stack.empty() || operator_stack.top() == '(') {
                    operand_stack.push(operand);
                    if (!operator_stack.empty()) {
                        operator_stack.pop();
                    }
                } else if (operator_stack.top() == '+') {
                    operand_stack.top() += operand;
                    operator_stack.pop();
                } else if (operator_stack.top() == '*') {
                    operand_stack.top() *= operand;
                    operator_stack.pop();
                }

            } else if (op == '*' || op == '+' || op == '(') {
                operator_stack.push(op);

            } else if (op == ')' && !operator_stack.empty()) {
                if (operator_stack.top() != '(') {
                    std::uint64_t value = operand_stack.top();
                    operand_stack.pop();

                    if (operator_stack.top() == '+') {
                        operand_stack.top() += value;
                    } else if (operator_stack.top() == '*') {
                        operand_stack.top() *= value;
                    }
                }
                operator_stack.pop();
            }
        }

        sum += operand_stack.top();
    }

    return sum;
}

int main() {
    std::string filename = "../../input/2020/day_18/input.txt";
    auto expressions = parse_file(filename);

    std::cout << "--- Day 18: Operation Order ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(expressions) << std::endl;
    benchmark::end(start);

    return 0;
}
