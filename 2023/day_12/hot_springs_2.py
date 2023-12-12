# --- Day 12: Hot Springs --- Part 2 ----

import time
from functools import cache


@cache
def get_recursive_sum(record, criteria, size=0):
    if len(record) == 0:
        return 1 if len(criteria) == 0 or (len(criteria) == 1 and criteria[0] == size) else 0

    arrangements = 0
    match record[0]:
        case '?':
            arrangements += get_recursive_sum(record.replace('?', '#', 1), criteria, size)
            arrangements += get_recursive_sum(record.replace('?', '.', 1), criteria, size)
        case '#':
            if len(criteria) > 0:
                arrangements += get_recursive_sum(record[1:], criteria, size + 1)
        case '.':
            if size > 0:
                if len(criteria) > 0:
                    if size == criteria[0]:
                        arrangements += get_recursive_sum(record[1:], criteria[1:])
            else:
                arrangements += get_recursive_sum(record[1:], criteria)

    return arrangements


if __name__ == '__main__':
    with open("hot_springs_input") as file:
        springs = file.read().strip().split("\n")

    start_time = time.perf_counter()
    sum_of_arrangements = 0
    for row in springs:
        recording, duplicates = row.split()
        duplicates = tuple([int(duplicate) for duplicate in duplicates.split(",")] * 5)

        new_recording = ""
        for i in range(5):
            new_recording += recording
            if i != 4:
                new_recording += '?'

        recording = new_recording

        unknowns = [char for char in recording if char == '?']
        result = get_recursive_sum(recording, duplicates)
        sum_of_arrangements += result

    print("Part 2:", sum_of_arrangements)
    print(f"Time: {time.perf_counter() - start_time}s")
