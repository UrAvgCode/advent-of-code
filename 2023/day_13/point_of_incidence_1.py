# --- Day 13: Point of Incidence --- Part One ----

from collections import deque


def find_equal_rows(pattern):
    pattern_list = []
    for i, (row, next_row) in enumerate(zip(pattern, pattern[1:])):
        if row == next_row:
            pattern_list.append(i + 1)
    return pattern_list


if __name__ == '__main__':
    with open("point_of_incidence_input") as file:
        patterns = [p.splitlines() for p in file.read().split("\n\n")]

    reflection_sum = 0
    for pattern in patterns:
        transpose = list(zip(*pattern))

        for mult, dir_pattern in enumerate((transpose, pattern)):
            for equal in find_equal_rows(dir_pattern):
                row_que = deque()
                for i, row in enumerate(dir_pattern):
                    if i < equal:
                        row_que.append(row)
                    elif row_que:
                        if row != row_que.pop():
                            break
                else:
                    if mult:
                        equal *= 100
                    reflection_sum += equal

    print("Part 1:", reflection_sum)
