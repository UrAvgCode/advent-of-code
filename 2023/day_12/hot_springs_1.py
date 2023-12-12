# --- Day 12: Hot Springs --- Part One ---

import re
import time


def get_recursive_sum(record, criteria):
    sum_value = 0

    if '?' not in record:
        return 1 if tuple([len(s) for s in re.split(r"\.+", record) if s != '']) == criteria else 0

    for symbol in ('#', '.'):
        record_modified = record.replace('?', symbol, 1)
        groups = []
        for group in re.split(r'\.+', record_modified):
            if group == '':
                continue
            if '?' in group:
                g = group[:group.index('?')]
                if len(g) > 0:
                    groups.append(g)
                break
            else:
                groups.append(group)

        if len(criteria) >= len(groups):
            for i, group in enumerate(groups):
                if len(group) > criteria[i]:
                    break
            else:
                sum_value += get_recursive_sum(record_modified, criteria)

    return sum_value


if __name__ == '__main__':
    with open("hot_springs_input") as file:
        springs = file.read().strip().split("\n")

    start_time = time.perf_counter()
    sum_of_arrangements = 0
    for row in springs:
        recording, duplicates = row.split()
        duplicates = tuple([int(duplicate) for duplicate in duplicates.split(",")])

        unknowns = [char for char in recording if char == '?']
        result = get_recursive_sum(recording, duplicates)
        sum_of_arrangements += result

    print("Part 1:", sum_of_arrangements)
    print(f"Time: {time.perf_counter() - start_time}s")
