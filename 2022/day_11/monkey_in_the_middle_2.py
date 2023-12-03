# --- Day 11: Monkey in the Middle --- Part Two ---

prime_numbers = (2, 3, 5, 7, 11, 13, 17, 19, 23)


class Item:
    def __init__(self, value):
        self.modulos = []
        for prime in prime_numbers:
            self.modulos.append(value % prime)

    def add(self, value):
        for prime in range(len(self.modulos)):
            self.modulos[prime] = (self.modulos[prime] + value) % prime_numbers[prime]

    def multiply(self, value):
        for prime in range(len(self.modulos)):
            self.modulos[prime] = (self.modulos[prime] * value) % prime_numbers[prime]

    def square(self):
        for prime in range(len(self.modulos)):
            self.modulos[prime] = (self.modulos[prime] * self.modulos[prime]) % prime_numbers[prime]

    def test(self, value):
        return self.modulos[prime_numbers.index(value)] == 0


class Monkey:
    def __init__(self, items, operation, test_number, true_monkey, false_monkey):
        self.items = items
        self.operation = operation
        self.test_number = test_number
        self.true_monkey = true_monkey
        self.false_monkey = false_monkey
        self.inspected_items = 0

    def pop(self, index):
        return self.items.pop(index)

    def append(self, item):
        self.items.append(item)

    def test(self, item):
        return item.test(self.test_number)

    def calculate_worry_level(self, item):
        if self.operation == ["*", "old"]:
            item.square()
        elif self.operation[0] == "+":
            item.add(int(self.operation[1]))
        elif self.operation[0] == "*":
            item.multiply(int(self.operation[1]))


if __name__ == '__main__':
    file = open("monkey_in_the_middle_input", "r")
    lines = file.readlines()

    monkeys = []
    for i in range(8):
        items_parts = lines[i * 7 + 1].replace(",", "").split()[2:]
        items = []
        for item in items_parts:
            items.append(Item(int(item)))
        operation = lines[i * 7 + 2].split()[4:]
        test = int(lines[i * 7 + 3].split()[-1])
        true_monkey = int(lines[i * 7 + 4].split()[-1])
        false_monkey = int(lines[i * 7 + 5].split()[-1])

        monkeys.append(Monkey(items, operation, test, true_monkey, false_monkey))

    for i in range(10000):
        for monkey in monkeys:
            for j in range(len(monkey.items)):
                new_item = monkey.pop(0)
                monkey.calculate_worry_level(new_item)

                monkey.inspected_items += 1
                if monkey.test(new_item):
                    monkeys[monkey.true_monkey].append(new_item)
                else:
                    monkeys[monkey.false_monkey].append(new_item)

    monkey_active_counts = []
    for monkey in monkeys:
        monkey_active_counts.append(monkey.inspected_items)
    monkey_active_counts.sort(reverse=True)

    print("Part 2: " + str(monkey_active_counts[0] * monkey_active_counts[1]))
