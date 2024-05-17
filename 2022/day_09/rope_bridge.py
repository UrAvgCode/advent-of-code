# --- Day 9: Rope Bridge ---
import math


class Knot:
    moveDict = {'U': (0, 1), 'D': (0, -1), 'R': (1, 0), 'L': (-1, 0)}

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def move(self, direction):
        self.x += self.moveDict[direction][0]
        self.y += self.moveDict[direction][1]

    def distance(self, other):
        return math.sqrt((self.x - other.x) ** 2 + (self.y - other.y) ** 2)


def sign(x):
    return (x > 0) - (x < 0)


def calculate_visited(knot_amount):
    knots = [Knot(0, 0) for _ in range(knot_amount)]

    visited = {(0, 0)}
    for direction, steps in motions:
        for _ in range(steps):
            knots[0].move(direction)
            for i, (prev_knot, knot) in enumerate(zip(knots, knots[1:]), start=1):
                if knot.distance(prev_knot) >= 2:
                    knot.x += sign(prev_knot.x - knot.x)
                    knot.y += sign(prev_knot.y - knot.y)
                    if i == knot_amount - 1:
                        visited.add((knot.x, knot.y))

    return len(visited)


if __name__ == '__main__':
    with open("../../input/2022/day_09/input.txt") as file:
        motions = [(d, int(s)) for d, s in (line.split() for line in file.read().splitlines())]

    print("Part 1:", calculate_visited(2))
    print("Part 2:", calculate_visited(10))
