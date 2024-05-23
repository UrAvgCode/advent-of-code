# --- Day 12: Hot Springs ---

import time
from functools import cache


@cache
def get_arrangements(record, criteria, size=0):
    if not record:
        return 1 if not criteria or (len(criteria) == 1 and criteria[0] == size) else 0

    arrangements = 0
    for case in ('#', '.') if record[0] == '?' else record[0]:
        if case == '#':
            if criteria:
                arrangements += get_arrangements(record[1:], criteria, size + 1)
        else:
            if 0 < size == criteria[0]:
                arrangements += get_arrangements(record[1:], criteria[1:])
            elif size == 0:
                arrangements += get_arrangements(record[1:], criteria)

    return arrangements


if __name__ == '__main__':
    with open("../../input/2023/day_12/input.txt") as file:
        springs = [row.split() for row in file.read().split("\n")]

    springs_list = []
    for record, criteria in springs:
        criteria = tuple(int(criteria) for criteria in criteria.split(","))
        springs_list.append((record, criteria))

    start_time = time.perf_counter()
    print("Part 1:", sum(
        get_arrangements(record, criteria)
        for record, criteria in springs_list))
    print(f"Time: {time.perf_counter() - start_time}s\n")

    start_time = time.perf_counter()
    print("Part 2:", sum(
        get_arrangements((("?" + record) * 5)[1:], criteria * 5)
        for record, criteria in springs_list
    ))
    print(f"Time: {time.perf_counter() - start_time}s")
