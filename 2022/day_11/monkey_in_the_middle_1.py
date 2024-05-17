# --- Day 11: Monkey in the Middle --- Part One ---

if __name__ == '__main__':
    with open('../../input/2022/day_11/input.txt') as file:
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
        monkeys.append([items, operation, test, true_monkey, false_monkey, 0])

    for _ in range(20):
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
                new_item //= 3

                monkey[-1] += 1
                if new_item % test == 0:
                    monkeys[true_monkey][0].append(new_item)
                else:
                    monkeys[false_monkey][0].append(new_item)

    monkey_active_counts = [monkey[-1] for monkey in monkeys]
    monkey_active_counts.sort(reverse=True)

    print('Part 1:', monkey_active_counts[0] * monkey_active_counts[1])
