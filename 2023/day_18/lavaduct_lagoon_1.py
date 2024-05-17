# --- Day 18: Lavaduct Lagoon --- Part One ---

from collections import deque

delta = {"U": (0, 1), "D": (0, -1), "R": (1, 0), "L": (-1, 0)}

if __name__ == '__main__':
    with open("../../input/2023/day_18/input.txt") as file:
        lines = file.read().splitlines()

    dig_plan = [(direction, int(x)) for direction, x, color in (line.split() for line in lines)]

    visited = set()
    current = (0, 0)
    for direction, amount in dig_plan:
        x, y = current
        dx, dy = delta[direction]

        for _ in range(amount):
            x, y = x + dx, y + dy
            current = (x, y)
            visited.add(current)

    min_x = min(x for x, y in visited) - 1
    max_x = max(x for x, y in visited) + 1
    min_y = min(y for x, y in visited) - 1
    max_y = max(y for x, y in visited) + 1
    map_area = (max_x - min_x + 1) * (max_y - min_y + 1)

    surrounding = set()
    fill_queue = deque([(min_x, min_y)])
    while fill_queue:
        current = fill_queue.popleft()
        if current in surrounding or current in visited:
            continue
        surrounding.add(current)

        x, y = current
        for dx, dy in delta.values():
            new_x, new_y = x + dx, y + dy
            if min_x <= new_x <= max_x and min_y <= new_y <= max_y:
                fill_queue.append((x + dx, y + dy))

    area = map_area - len(surrounding)
    print("Part 1:", area)
