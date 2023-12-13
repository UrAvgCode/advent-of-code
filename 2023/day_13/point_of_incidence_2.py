# --- Day 13: Point of Incidence --- Part Two ----

from collections import deque

if __name__ == '__main__':
    with open("point_of_incidence_input") as file:
        patterns = [p.splitlines() for p in file.read().split("\n\n")]

    reflection_sum = 0
    for pattern in patterns:
        transpose = list(zip(*pattern))

        for mult, dir_pattern in enumerate((transpose, pattern)):
            for equal in range(len(dir_pattern)):
                row_que = deque()
                difference = 0
                for i, row in enumerate(dir_pattern):
                    if i < equal:
                        row_que.append(row)
                    elif row_que:
                        for char, char2 in zip(row, row_que.pop()):
                            if char != char2:
                                difference += 1
                        if difference > 1:
                            break
                else:
                    if mult:
                        equal *= 100
                    if difference == 1:
                        reflection_sum += equal

    print("Part 2:", reflection_sum)
