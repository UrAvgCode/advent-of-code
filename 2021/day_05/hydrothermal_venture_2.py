# --- Day 5: Hydrothermal Venture --- Part One ---

def sign(x):
    return (x > 0) - (x < 0)


if __name__ == '__main__':
    with open('hydrothermal_venture_input') as file:
        lines = file.read().splitlines()

    vents = []
    for line in lines:
        start, end = line.split(' -> ')
        start = tuple(map(int, start.split(',')))
        end = tuple(map(int, end.split(',')))
        vents.append((start, end))

    diagram = {}
    for vent in vents:
        (x1, y1), (x2, y2) = vent
        while x1 != x2 or y1 != y2:
            diagram[(x1, y1)] = diagram.get((x1, y1), 0) + 1
            x1 += sign(x2 - x1)
            y1 += sign(y2 - y1)
        diagram[(x1, y1)] = diagram.get((x1, y1), 0) + 1

    overlaps = sum(1 for value in diagram.values() if value > 1)
    print('Part 2:', overlaps)
