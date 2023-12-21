# --- Day 21: Step Counter ---

from collections import deque

if __name__ == '__main__':
    with open('step_counter_input') as file:
        garden_map = file.read().splitlines()

    start = (0, 0, 0)
    for y in range(len(garden_map)):
        for x in range(len(garden_map[y])):
            if garden_map[y][x] == 'S':
                start = (x, y, 0)
                break

    possible_plots = 0
    step_history = set()
    step_queue = deque([start])
    while step_queue:
        x, y, steps = step_queue.popleft()

        if (x, y, steps) in step_history:
            continue

        step_history.add((x, y, steps))

        if steps == 64:
            possible_plots += 1
            continue

        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            new_x, new_y = x + dx, y + dy
            if 0 <= new_x < len(garden_map[y]) and 0 <= new_y < len(garden_map) and garden_map[new_y][new_x] != '#':
                step_queue.append((new_x, new_y, steps + 1))

    print("Part 1:", possible_plots)
