# --- Day 16: The Floor Will Be Lava ---

from collections import deque

directions = {'E': (1, 0), 'W': (-1, 0), 'N': (0, -1), 'S': (0, 1)}
right_mirror = {'E': 'N', 'W': 'S', 'N': 'E', 'S': 'W'}
left_mirror = {'E': 'S', 'W': 'N', 'N': 'W', 'S': 'E'}


def get_energized_tiles(grid, start_beam=(-1, 0, 'E')):
    beam_queue = deque([start_beam])
    energized_tiles = set()
    beam_history = set()

    while beam_queue:
        x, y, direction = beam_queue.pop()
        if (x, y, direction) in beam_history:
            continue

        energized_tiles.add((x, y))
        beam_history.add((x, y, direction))

        dx, dy = directions[direction]
        next_x, next_y = x + dx, y + dy

        if next_x < 0 or next_y < 0 or next_y >= len(grid) or next_x >= len(grid[next_y]):
            continue

        match grid[next_y][next_x]:
            case '.':
                beam_queue.append((next_x, next_y, direction))
            case '|':
                if direction in ('N', 'S'):
                    beam_queue.append((next_x, next_y, direction))
                else:
                    beam_queue.append((next_x, next_y, 'N'))
                    beam_queue.append((next_x, next_y, 'S'))
            case '-':
                if direction in ('E', 'W'):
                    beam_queue.append((next_x, next_y, direction))
                else:
                    beam_queue.append((next_x, next_y, 'E'))
                    beam_queue.append((next_x, next_y, 'W'))
            case '/':
                beam_queue.append((next_x, next_y, right_mirror[direction]))
            case '\\':
                beam_queue.append((next_x, next_y, left_mirror[direction]))
    return len(energized_tiles) - 1


if __name__ == '__main__':
    with open("../../input/2023/day_16/input.txt") as file:
        grid = file.read().splitlines()

    energized_list = []
    for i in range(len(grid)):
        energized_list.append(get_energized_tiles(grid, (i, -1, 'S')))
        energized_list.append(get_energized_tiles(grid, (i, len(grid), 'N')))
        energized_list.append(get_energized_tiles(grid, (-1, i, 'E')))
        energized_list.append(get_energized_tiles(grid, (len(grid[i]), i, 'W')))

    print("Part 1:", get_energized_tiles(grid))
    print("Part 2:", max(energized_list))
