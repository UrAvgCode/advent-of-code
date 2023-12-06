# --- Day 6: Wait For It ---

import math


def get_number_of_ways(time, distance):
    root = math.sqrt(time ** 2 - 4 * (distance + 1))
    start = (time - root) / 2
    end = (time + root) / 2
    return math.floor(end) - math.ceil(start) + 1


if __name__ == '__main__':
    with open("wait_for_it_input") as file:
        times, distances = file.read().strip().split("\n")

    times_part1 = [int(time) for time in times.split()[1:]]
    distances_part1 = [int(distance) for distance in distances.split()[1:]]

    time_part2 = int(times.split(" ", 1)[1].replace(" ", ""))
    distance_part2 = int(distances.split(" ", 1)[1].replace(" ", ""))

    ways_multiplied = 1
    for time, distance in zip(times_part1, distances_part1):
        ways_multiplied *= get_number_of_ways(time, distance)

    print("Part 1:", ways_multiplied)
    print("Part 2:", get_number_of_ways(time_part2, distance_part2))
