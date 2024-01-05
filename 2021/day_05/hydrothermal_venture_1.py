# --- Day 5: Hydrothermal Venture --- Part One ---

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
        if x1 == x2 or y1 == y2:
            for x in range(min(x1, x2), max(x1, x2) + 1):
                for y in range(min(y1, y2), max(y1, y2) + 1):
                    diagram[(x, y)] = diagram.get((x, y), 0) + 1

    overlaps = sum(1 for value in diagram.values() if value > 1)

    print('Part 1:', overlaps)
