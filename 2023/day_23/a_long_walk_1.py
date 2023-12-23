# --- Day 23: A Long Walk --- Part One ---

from collections import deque
from time import perf_counter

if __name__ == '__main__':
    with open('a_long_walk_input') as file:
        hiking_trails = file.read().splitlines()

    start_time = perf_counter()

    map_height = len(hiking_trails)
    map_width = len(hiking_trails[0])
    goal = (map_width - 2, map_height - 1)

    move_queue = deque([(0, 1, 0, set())])
    possible_paths = []
    while move_queue:
        steps, x, y, visited = move_queue.popleft()

        if (x, y) in visited:
            continue

        if (x, y) == goal:
            possible_paths.append(steps)
            continue

        visited.add((x, y))

        match hiking_trails[y][x]:
            case '#':
                continue
            case '>':
                directions = [(1, 0)]
            case '<':
                directions = [(-1, 0)]
            case '^':
                directions = [(0, -1)]
            case 'v':
                directions = [(0, 1)]
            case _:
                directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        for dx, dy in directions:
            new_x, new_y = x + dx, y + dy
            if 0 <= new_y and hiking_trails[new_y][new_x] != '#':
                move_queue.append((steps + 1, new_x, new_y, visited.copy()))

    print('Part 1:', max(possible_paths))
    print('Time:', perf_counter() - start_time)
