# --- Day 5: If You Give A Seed A Fertilizer ---

from collections import deque


def get_locations(seeds, categories):
    locations = []
    for seed in seeds:
        value = seed
        for category in categories:
            for dst_start, src_start, length in category:
                if src_start <= value < src_start + length:
                    value += dst_start - src_start
                    break
        locations.append(value)
    return locations


def get_location_ranges(seed_ranges, categories):
    location_ranges = []
    for seed in seed_ranges:
        values = deque([seed])
        for category in categories:
            new_values = deque()
            while values:
                current_start, current_length = values.pop()
                for dst_start, src_start, length in category:
                    translation = dst_start - src_start
                    start = max(current_start, src_start)
                    end = min(current_start + current_length, src_start + length)

                    if start < end:
                        new_start = start + translation
                        new_length = end - start
                        new_values.append((new_start, new_length))

                        if current_start < start:
                            values.append((current_start, start - current_start))
                        if current_start + current_length > end:
                            values.append((end, current_start + current_length - end))
                        break
                else:
                    new_values.append((current_start, current_length))
            values = list(new_values)
        location_ranges.extend(values)
    return location_ranges


if __name__ == '__main__':
    with open("../../input/2023/day_05/input.txt") as file:
        almanac = file.read().split("\n\n")

    seeds = list(map(int, almanac[0].split()[1:]))
    seed_ranges = list(zip(seeds[::2], seeds[1::2]))
    categories = [[tuple(map(int, line.split())) for line in group.splitlines()[1:]] for group in almanac[1:]]

    locations = get_locations(seeds, categories)
    location_ranges = get_location_ranges(seed_ranges, categories)

    print("Part 1:", min(locations))
    print("Part 2:", min([location[0] for location in location_ranges]))
