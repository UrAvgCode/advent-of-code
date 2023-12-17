# --- Day 17: Reservoir Research ---

from heapq import heappop, heappush
from time import perf_counter


def get_min_heat_loss(heat_map, braking_duration=0, maximum_speed=3):
    crucible_queue = [(0, 0, 0, 0, 0, 0)]
    crucible_history = set()

    rows, columns = len(heat_map), len(heat_map[0])
    destination = (columns - 1, rows - 1)

    while crucible_queue:
        heat_loss, x, y, x_dir, y_dir, speed = heappop(crucible_queue)

        state = (x, y, x_dir, y_dir, speed)
        if state in crucible_history:
            continue
        crucible_history.add(state)

        if (x, y) == destination and speed >= braking_duration:
            return heat_loss

        if speed >= braking_duration or not speed:
            if not x_dir:
                for i in (1, -1):
                    if 0 <= x + i < columns:
                        heappush(crucible_queue, (heat_loss + heat_map[y][x + i], x + i, y, i, 0, 1))
            if not y_dir:
                for i in (1, -1):
                    if 0 <= y + i < rows:
                        heappush(crucible_queue, (heat_loss + heat_map[y + i][x], x, y + i, 0, i, 1))

        if speed < maximum_speed:
            new_x, new_y = x + x_dir, y + y_dir
            if 0 <= new_x < rows and 0 <= new_y < columns:
                heappush(crucible_queue, (heat_loss + heat_map[new_y][new_x], new_x, new_y, x_dir, y_dir, speed + 1))


if __name__ == '__main__':
    with open("reservoir_research_input") as file:
        lines = file.read().splitlines()

    heat_map = tuple(tuple(int(char) for char in line) for line in lines)

    start_time = perf_counter()
    print("Part 1:", get_min_heat_loss(heat_map))
    print("Time: ", perf_counter() - start_time)

    start_time = perf_counter()
    print("\nPart 2:", get_min_heat_loss(heat_map, 4, 10))
    print("Time: ", perf_counter() - start_time)
