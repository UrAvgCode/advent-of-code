# --- Day 11: Monkey in the Middle ---

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

    def test(self, number):
        return number % self.test_number == 0

    def calculate_worry_level(self, item):
        if self.operation == ["*", "old"]:
            return item * item
        elif self.operation[0] == "+":
            return item + int(self.operation[1])
        elif self.operation[0] == "*":
            return item * int(self.operation[1])


if __name__ == '__main__':
    file = open("monkey_in_the_middle_input", "r")
    lines = file.readlines()

    monkeys = []
    for i in range(8):
        items_parts = lines[i * 7 + 1].replace(",", "").split()[2:]
        items = []
        for item in items_parts:
            items.append(int(item))
        operation = lines[i * 7 + 2].split()[4:]
        test = int(lines[i * 7 + 3].split()[-1])
        true_monkey = int(lines[i * 7 + 4].split()[-1])
        false_monkey = int(lines[i * 7 + 5].split()[-1])

        monkeys.append(Monkey(items, operation, test, true_monkey, false_monkey))

    for i in range(20):
        for monkey in monkeys:
            for j in range(len(monkey.items)):
                new_item = monkey.calculate_worry_level(monkey.pop(0))
                new_item //= 3
                monkey.inspected_items += 1
                if monkey.test(new_item):
                    monkeys[monkey.true_monkey].append(new_item)
                else:
                    monkeys[monkey.false_monkey].append(new_item)

    monkey_active_counts = []
    for monkey in monkeys:
        monkey_active_counts.append(monkey.inspected_items)
    monkey_active_counts.sort(reverse=True)

    print("Part 1: " + str(monkey_active_counts[0] * monkey_active_counts[1]))
