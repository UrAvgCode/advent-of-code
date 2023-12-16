# --- Day 16: The Floor Will Be Lava ---

from collections import deque


def get_energized_tiles(start_beam=(-1, 0, 'E')):
    beam_queue = deque([start_beam])
    energized_tiles = set()
    beam_history = set()

    while beam_queue:
        beam = beam_queue.pop()
        if beam in beam_history:
            continue

        x, y, direction = beam
        energized_tiles.add((x, y))
        beam_history.add((x, y, direction))

        match direction:
            case 'E':
                next_x = x + 1
                next_y = y
            case 'W':
                next_x = x - 1
                next_y = y
            case 'N':
                next_x = x
                next_y = y - 1
            case 'S':
                next_x = x
                next_y = y + 1
            case _:
                next_x = next_y = -1

        if next_x < 0 or next_y < 0 or next_y >= len(lines) or next_x >= len(lines[next_y]):
            continue

        match lines[next_y][next_x]:
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
                match direction:
                    case 'E':
                        new_dir = 'N'
                    case 'W':
                        new_dir = 'S'
                    case 'N':
                        new_dir = 'E'
                    case 'S':
                        new_dir = 'W'
                    case _:
                        new_dir = None
                beam_queue.append((next_x, next_y, new_dir))
            case '\\':
                match direction:
                    case 'E':
                        new_dir = 'S'
                    case 'W':
                        new_dir = 'N'
                    case 'N':
                        new_dir = 'W'
                    case 'S':
                        new_dir = 'E'
                    case _:
                        new_dir = None
                beam_queue.append((next_x, next_y, new_dir))
    return len(energized_tiles) - 1


if __name__ == '__main__':
    with open("the_floor_will_be_lava_input") as file:
        lines = [list(line) for line in file.read().splitlines()]

    energized_list = []
    for y in range(len(lines)):
        energized_list.append(get_energized_tiles((-1, y, 'E')))
        energized_list.append(get_energized_tiles((len(lines[0]), y, 'W')))

    for x in range(len(lines[0])):
        energized_list.append(get_energized_tiles((x, -1, 'S')))
        energized_list.append(get_energized_tiles((x, len(lines), 'N')))

    print("Part 1:", get_energized_tiles())
    print("Part 2:", max(energized_list))
