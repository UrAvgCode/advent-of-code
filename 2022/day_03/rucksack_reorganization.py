# --- Day 3: Rucksack Reorganization ---

import string

if __name__ == '__main__':
    with open("../../input/2022/day_03/input.txt") as file:
        rucksacks = file.read().strip().split("\n")

    priorities = {item: i + 1 for i, item in enumerate(string.ascii_letters)}
    priorities_one = 0
    priorities_two = 0

    for i, rucksack in enumerate(rucksacks):
        second_compartment = set(rucksack[len(rucksack) // 2:])
        item = next(item for item in rucksack if item in second_compartment)
        priorities_one += priorities[item]

        if i % 3 == 0 and i + 2 < len(rucksacks):
            item_set = set(rucksacks[i + 1]) & set(rucksacks[i + 2])
            item = next(item for item in rucksack if item in item_set)
            priorities_two += priorities[item]

    print("Part 1:", priorities_one)
    print("Part 2:", priorities_two)
