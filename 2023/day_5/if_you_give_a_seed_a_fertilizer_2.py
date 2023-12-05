# --- Day 5: If You Give A Seed A Fertilizer --- Part Two ---

if __name__ == '__main__':
    file = open("if_you_give_a_seed_a_fertilizer_input", "r")
    lines = file.readlines()

    categories = ("seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light",
                  "light-to-temperature", "temperature-to-humidity", "humidity-to-location")

    maps = {"seed-to-soil": [], "soil-to-fertilizer": [], "fertilizer-to-water": [], "water-to-light": [],
            "light-to-temperature": [], "temperature-to-humidity": [], "humidity-to-location": []}

    current_category = "seeds:"
    seed_ranges = []

    for line in lines:
        parts = line.split()

        if len(parts) > 0:
            if parts[0] == "seeds:":
                for i in range(1, len(parts), 2):
                    seed_ranges.append((int(parts[i]), int(parts[i]) + int(parts[i + 1]) - 1))
            elif parts[0] in maps:
                current_category = parts[0]
            else:
                destination_range = (int(parts[0]), int(parts[0]) + int(parts[2]))
                source_range = (int(parts[1]), int(parts[1]) + int(parts[2]))
                maps[current_category].append((source_range, destination_range))

    location_ranges = []
    for seeds in seed_ranges:
        values = [seeds]
        for category in categories:
            new_values = []
            while len(values) > 0:
                value_range = values.pop()

                for src_dest_map in maps[category]:
                    source = src_dest_map[0]
                    dest = src_dest_map[1]
                    dest_translations = dest[0] - source[0]

                    start = max(value_range[0], source[0])
                    end = min(value_range[1], source[1])

                    if start < end:
                        new_start = start + dest_translations
                        new_end = end + dest_translations

                        new_values.append((new_start, new_end))

                        if value_range[0] < start:
                            values.append((value_range[0], start))
                        if value_range[1] > end:
                            values.append((end, value_range[1]))
                        break
                else:
                    new_values.append(value_range)

            values = list(new_values)

        location_ranges.extend(values)

    start_locations = []
    for location in location_ranges:
        start_locations.append(location[0])

    print("Part 2:", min(start_locations))
