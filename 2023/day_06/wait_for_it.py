# --- Day 6: Wait For It ---

import math


def get_number_of_ways(time, distance):
    root = math.sqrt(time ** 2 - 4 * (distance + 1))
    start = (time - root) / 2
    end = (time + root) / 2
    return math.floor(end) - math.floor(start)


if __name__ == '__main__':
    with open("wait_for_it_input") as file:
        times, distances = file.read().splitlines()

    times_part_one = [int(time) for time in times.split()[1:]]
    distances_part_one = [int(distance) for distance in distances.split()[1:]]

    time_part_two = int(times.split(" ", 1)[1].replace(" ", ""))
    distance_part_two = int(distances.split(" ", 1)[1].replace(" ", ""))

    ways_multiplied = 1
    for time, distance in zip(times_part_one, distances_part_one):
        ways_multiplied *= get_number_of_ways(time, distance)

    print("Part 1:", ways_multiplied)
    print("Part 2:", get_number_of_ways(time_part_two, distance_part_two))
