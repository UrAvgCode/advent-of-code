# --- Day 5: Supply Stacks ---

from collections import deque

if __name__ == '__main__':
    with open("supply_stacks_input") as file:
        start_stacks, instructions = file.read().split("\n\n")

    amounts, *start_stacks = reversed(start_stacks.split("\n"))
    amount = int(amounts.split()[-1])

    stacks_one = [deque() for _ in range(amount)]
    stacks_two = [deque() for _ in range(amount)]
    for row in start_stacks:
        for i in range(amount):
            if row[1 + i * 4] != " ":
                stacks_one[i].append(row[1 + i * 4])
                stacks_two[i].append(row[1 + i * 4])

    for instruction in instructions.split("\n"):
        repetitions, source, dest = [int(i) for i in instruction.split()[1::2]]
        crates = deque([stacks_two[source - 1].pop() for _ in range(repetitions)])
        for i in range(repetitions):
            stacks_one[dest - 1].append(stacks_one[source - 1].pop())
            stacks_two[dest - 1].append(crates.pop())

    top_crates_one = "".join([stack.pop() for stack in stacks_one])
    top_crates_two = "".join([stack.pop() for stack in stacks_two])

    print("Part 1:", top_crates_one)
    print("Part 2:", top_crates_two)
