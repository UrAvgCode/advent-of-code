// --- Day 18: Operation Order ---

#include "solver.h"

#include <fstream>
#include <stack>
#include <string>

std::vector<std::string> parser(std::ifstream &file) {
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

        for (char token: expression) {
            if (std::isdigit(token)) {
                int operand = token - '0';
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

            } else if (token == '+' || token == '*' || token == '(') {
                operator_stack.push(token);

            } else if (token == ')') {
                if (!operator_stack.empty()) {
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
        }

        sum += operand_stack.top();
    }

    return sum;
}

std::uint64_t part_two(const std::vector<std::string> &expressions) {
    std::uint64_t sum = 0;
    for (const auto &expression: expressions) {
        std::stack<std::uint64_t> operand_stack;
        std::stack<char> operator_stack;

        for (char token: expression) {
            if (token == ' ') {
                continue;

            } else if (std::isdigit(token)) {
                int operand = token - '0';
                if (operator_stack.empty() || operator_stack.top() == '(' || operator_stack.top() == '*') {
                    operand_stack.push(operand);
                } else if (operator_stack.top() == '+') {
                    operand_stack.top() += operand;
                    operator_stack.pop();
                }

            } else if (token == '+' || token == '*' || token == '(') {
                operator_stack.push(token);

            } else if (token == ')') {
                while (operator_stack.top() != '(') {
                    std::uint64_t value = operand_stack.top();
                    operand_stack.pop();

                    if (operator_stack.top() == '+') {
                        operand_stack.top() += value;
                    } else if (operator_stack.top() == '*') {
                        operand_stack.top() *= value;
                    }
                    operator_stack.pop();
                }
                operator_stack.pop();

                if (!operator_stack.empty() && operator_stack.top() == '+') {
                    std::uint64_t value = operand_stack.top();
                    operand_stack.pop();

                    operand_stack.top() += value;
                    operator_stack.pop();
                }
            }
        }

        while (!operator_stack.empty()) {
            std::uint64_t value = operand_stack.top();
            operand_stack.pop();

            if (operator_stack.top() == '+') {
                operand_stack.top() += value;
            } else if (operator_stack.top() == '*') {
                operand_stack.top() *= value;
            }
            operator_stack.pop();
        }

        sum += operand_stack.top();
    }

    return sum;
}

int main() {
    Solver solver(2020, 18, "Operation Order");

    auto expressions = solver.parse_file(parser);
    solver(part_one, expressions);
    solver(part_two, expressions);

    return 0;
}
