# --- Day 18: Lavaduct Lagoon --- Part Two ---

from shapely.geometry import Polygon

delta = [(1, 0), (0, -1), (-1, 0), (0, 1)]

if __name__ == '__main__':
    with open("lavaduct_lagoon_input") as file:
        lines = file.read().splitlines()

    dig_plan = []
    for instruction in [line.split()[2] for line in lines]:
        direction = int(instruction[7])
        amount = int(instruction[2:7], 16)
        dig_plan.append((direction, amount))

    current = (0, 0)
    perimeter = 0
    edges = []
    for instruction in dig_plan:
        direction, amount = instruction
        x, y = current
        dx, dy = delta[direction]

        new_x = x + dx * amount
        new_y = y + dy * amount

        perimeter += amount
        edges.append((new_x, new_y))
        current = (new_x, new_y)

    polygon = Polygon(edges)
    area = polygon.area + perimeter // 2 + 1
    print("Part 2:", int(area))
