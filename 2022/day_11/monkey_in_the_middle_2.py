# --- Day 11: Monkey in the Middle --- Part Two ---

from time import perf_counter

primes = (2, 3, 5, 7, 11, 13, 17, 19, 23)


class Item:
    def __init__(self, value):
        self.modulos = {prime: value % prime for prime in primes}

    def __add__(self, other):
        for prime in primes:
            self.modulos[prime] = (self.modulos[prime] + other) % prime
        return self

    def __mul__(self, other):
        for prime in primes:
            self.modulos[prime] = (self.modulos[prime] * other) % prime
        return self

    def __mod__(self, other):
        return self.modulos[other]

    def __pow__(self, other):
        for prime in primes:
            self.modulos[prime] = pow(self.modulos[prime], other) % prime
        return self


if __name__ == '__main__':
    with open('monkey_in_the_middle_input') as file:
        monkey_strings = file.read().split('\n\n')

    monkeys = []
    for i, monkey in enumerate(monkey_strings):
        m, items, operation, test, true_monkey, false_monkey = monkey.splitlines()
        items = list(map(int, items.replace(',', '').split()[2:]))
        operation = operation.split()
        operation = (operation[4], operation[5])
        test = int(test.split()[-1])
        true_monkey = int(true_monkey.split()[-1])
        false_monkey = int(false_monkey.split()[-1])
        monkeys.append([list(map(Item, items)), operation, test, true_monkey, false_monkey, 0])

    for _ in range(10000):
        for monkey in monkeys:
            items, operation, test, true_monkey, false_monkey, inspected = monkey
            while items:
                new_item = items.pop()
                operator, operand = operation
                if operand == 'old':
                    new_item = new_item ** 2
                elif operator == '+':
                    new_item += int(operand)
                elif operator == '*':
                    new_item *= int(operand)

                monkey[-1] += 1
                if new_item % test == 0:
                    monkeys[true_monkey][0].append(new_item)
                else:
                    monkeys[false_monkey][0].append(new_item)

    monkey_active_counts = [monkey[-1] for monkey in monkeys]
    monkey_active_counts.sort(reverse=True)

    print('Part 2:', monkey_active_counts[0] * monkey_active_counts[1])
