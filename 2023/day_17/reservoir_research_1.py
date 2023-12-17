# --- Day 17: Reservoir Research --- Part One ---

from bisect import insort

if __name__ == '__main__':
    with open("reservoir_research_input") as file:
        lines = file.read().splitlines()

    heat_map = tuple(tuple(int(char) for char in line) for line in lines)

    # heat_loss, x, y, x_dir, y_dir, moves_count
    crucible_queue = [(0, 0, 0, 1, 0, 0)]
    crucible_history = dict()

    min_heat_loss = 999999
    while crucible_queue:
        heat_loss, x, y, x_dir, y_dir, moves_count = crucible_queue.pop(0)

        if heat_loss >= min_heat_loss:
            continue

        if (x, y, x_dir, y_dir, moves_count) in crucible_history:
            if crucible_history[(x, y, x_dir, y_dir, moves_count)] <= heat_loss:
                continue

        crucible_history[(x, y, x_dir, y_dir, moves_count)] = heat_loss

        if x == len(heat_map[y]) - 1 and y == len(heat_map) - 1:
            min_heat_loss = heat_loss
            break

        next_x, next_y = x + x_dir, y + y_dir
        if moves_count < 3 and 0 <= next_x < len(heat_map[0]) and 0 <= next_y < len(heat_map):
            insort(crucible_queue,
                   (heat_loss + heat_map[next_y][next_x], next_x, next_y, x_dir, y_dir, moves_count + 1))

        if not x_dir:
            if x + 1 < len(heat_map[y]):
                insort(crucible_queue, (heat_loss + heat_map[y][x + 1], x + 1, y, 1, 0, 1))
            if x - 1 >= 0:
                insort(crucible_queue, (heat_loss + heat_map[y][x - 1], x - 1, y, -1, 0, 1))
        elif not y_dir:
            if y + 1 < len(heat_map):
                insort(crucible_queue, (heat_loss + heat_map[y + 1][x], x, y + 1, 0, 1, 1))
            if y - 1 >= 0:
                insort(crucible_queue, (heat_loss + heat_map[y - 1][x], x, y - 1, 0, -1, 1))

    print("Part 1:", min_heat_loss)
