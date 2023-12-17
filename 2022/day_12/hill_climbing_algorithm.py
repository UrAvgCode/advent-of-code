# --- Day 12: Hill Climbing Algorithm ---

from collections import deque


def height(char):
    if char == 'S':
        return ord('a')
    elif char == 'E':
        return ord('z')
    else:
        return ord(char)


def find_shortest_path(heightmap, start):
    move_queue = deque([start])
    visited = set()

    while move_queue:
        x, y, moves = move_queue.popleft()

        if (x, y) in visited:
            continue
        visited.add((x, y))

        if heightmap[y][x] == 'E':
            return moves

        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            new_x, new_y = x + dx, y + dy
            if 0 <= new_x < len(heightmap[y]) and 0 <= new_y < len(heightmap) and height(heightmap[y][x]) >= height(
                    heightmap[new_y][new_x]) - 1:
                move_queue.append((new_x, new_y, moves + 1))

    return float('inf')


if __name__ == '__main__':
    with open("hill_climbing_algorithm_input") as file:
        heightmap = file.read().splitlines()

    distance_from_start = float('inf')
    min_distance = float('inf')
    for y, row in enumerate(heightmap):
        for x, char in enumerate(row):
            if char == 'a':
                distance = find_shortest_path(heightmap, (x, y, 0))
                min_distance = min(min_distance, distance)
            elif char == 'S':
                distance_from_start = find_shortest_path(heightmap, (x, y, 0))

    print("Part 1:", distance_from_start)
    print("Part 2:", min_distance)
