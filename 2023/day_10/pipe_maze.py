# --- Day 10: Pipe Maze ---

from collections import deque


def next_pipe(current, last):
    match pipe_map[current[0]][current[1]]:
        case '|':
            if last[0] == current[0]:
                return "Stop"
            else:
                return 2 * current[0] - last[0], current[1]
        case '-':
            if last[0] != current[0]:
                return "Stop"
            else:
                return current[0], 2 * current[1] - last[1]
        case 'L':
            if last[1] < current[1] or last[0] > current[0]:
                return "Stop"
            elif last[0] == current[0]:
                return current[0] - 1, current[1]
            else:
                return current[0], current[1] + 1
        case 'J':
            if last[1] > current[1] or last[0] > current[0]:
                return "Stop"
            elif last[0] == current[0]:
                return current[0] - 1, current[1]
            else:
                return current[0], current[1] - 1
        case '7':
            if last[1] > current[1] or last[0] < current[0]:
                return "Stop"
            elif last[0] == current[0]:
                return current[0] + 1, current[1]
            else:
                return current[0], current[1] - 1
        case 'F':
            if last[1] < current[1] or last[0] < current[0]:
                return "Stop"
            if last[0] == current[0]:
                return current[0] + 1, current[1]
            else:
                return current[0], current[1] + 1
        case '.':
            return "Stop"
        case 'S':
            return "Start"


def find_loop(start, last):
    visited = []
    last = last
    current = start
    while current not in visited:
        visited.append(current)
        p_last = current
        current = next_pipe(current, last)
        last = p_last
        if current == "Start":
            return True, visited
        elif current == "Stop":
            return False, visited
        elif current[0] < 0 or current[1] < 0:
            return False, visited
    return False, visited


if __name__ == '__main__':
    with open("pipe_maze_input") as file:
        pipe_map = file.read().strip().split("\n")

        start = (0, 0)
        for y in range(len(pipe_map)):
            for x in range(len(pipe_map[y])):
                if pipe_map[y][x] == 'S':
                    start = (y, x)

        loop = False
        visited = []
        for y_dir in range(-1, 2, 2):
            loop, visited = find_loop((start[0] + y_dir, start[1]), start)
            if loop:
                break
        else:
            for x_dir in range(-1, 2, 2):
                loop, visited = find_loop((start[0], start[1] + x_dir), start)
                if loop:
                    break

        new_map = []
        for y, row in enumerate(pipe_map):
            new_row = []
            new_row_2 = []
            for x, tile in enumerate(row):
                if (y, x) in visited:
                    new_row.append(tile)
                    if tile == 'S' and pipe_map[y][x + 1] in "-J7":
                        new_row.append('N')
                    elif tile in "-LF":
                        new_row.append('N')
                    else:
                        new_row.append('.')
                    if tile == 'S' and pipe_map[y + 1][x] in "|LJ":
                        new_row_2.append('N')
                    elif tile in "|7F":
                        new_row_2.append('N')
                    else:
                        new_row_2.append('.')
                    new_row_2.append('.')
                else:
                    new_row.extend(['.', '.'])
                    new_row_2.extend(['.', '.'])

            new_map.append(new_row)
            new_map.append(new_row_2)

        fill_queue = deque([(0, 0)])
        filled = set()
        while len(fill_queue) > 0:
            current = fill_queue.popleft()
            if current in filled or new_map[current[0]][current[1]] != '.':
                continue
            filled.add(current)

            if current[0] > 0:
                fill_queue.append((current[0] - 1, current[1]))
            if current[1] > 0:
                fill_queue.append((current[0], current[1] - 1))
            if current[0] < len(new_map) - 1:
                fill_queue.append((current[0] + 1, current[1]))
            if current[1] < len(new_map[0]) - 1:
                fill_queue.append((current[0], current[1] + 1))

        count = sum(
            1 for y in range(0, len(new_map), 2)
            for x in range(0, len(new_map[y]), 2)
            if (y, x) not in filled and new_map[y][x] == '.'
        )

        print("Part 1:", len(visited) // 2)
        print("Part 2:", count)
