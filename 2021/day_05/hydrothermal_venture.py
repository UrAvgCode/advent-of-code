# --- Day 5: Hydrothermal Venture ---

def sign(x):
    return (x > 0) - (x < 0)


def calculate_overlaps(vents, diagonals=False):
    diagram = {}
    for vent in vents:
        (x1, y1), (x2, y2) = vent
        if diagonals or x1 == x2 or y1 == y2:
            while x1 != x2 or y1 != y2:
                diagram[(x1, y1)] = diagram.get((x1, y1), 0) + 1
                x1 += sign(x2 - x1)
                y1 += sign(y2 - y1)
            diagram[(x2, y2)] = diagram.get((x2, y2), 0) + 1

    return sum(1 for value in diagram.values() if value > 1)


if __name__ == '__main__':
    with open('../../input/2021/day_05/input.txt') as file:
        lines = file.read().splitlines()

    vents = []
    for line in lines:
        start, end = line.split(' -> ')
        start = tuple(map(int, start.split(',')))
        end = tuple(map(int, end.split(',')))
        vents.append((start, end))

    print('Part 1:', calculate_overlaps(vents))
    print('Part 2:', calculate_overlaps(vents, True))
