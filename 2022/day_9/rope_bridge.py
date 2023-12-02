# --- Day 9: Rope Bridge ---
import math


def sign(x):
    if x < 0:
        return -1
    elif x > 0:
        return 1
    else:
        return 0


def calculate_visited(knot_amount, inputs):
    knots_x = [0 for _ in range(knot_amount)]
    knots_y = [0 for _ in range(knot_amount)]

    visited = {"0,0"}

    for line in inputs:
        steps = int(line.split()[1])

        for i in range(steps):
            if line[0] == "U":
                knots_y[0] += 1
            elif line[0] == "D":
                knots_y[0] -= 1
            elif line[0] == "R":
                knots_x[0] += 1
            elif line[0] == "L":
                knots_x[0] -= 1

            for j in range(1, len(knots_x)):
                distance = math.sqrt((knots_x[j - 1] - knots_x[j]) ** 2 + (knots_y[j - 1] - knots_y[j]) ** 2)
                if distance >= 2:
                    knots_x[j] += sign(knots_x[j - 1] - knots_x[j])
                    knots_y[j] += sign(knots_y[j - 1] - knots_y[j])
                    if j == len(knots_x) - 1:
                        visited.add(str(knots_x[j]) + "," + str(knots_y[j]))

    return len(visited)


if __name__ == '__main__':
    file = open("rope_bridge_input", "r")
    lines = file.readlines()

    print("Part 1: " + str(calculate_visited(2, lines)))
    print("Part 2: " + str(calculate_visited(10, lines)))
