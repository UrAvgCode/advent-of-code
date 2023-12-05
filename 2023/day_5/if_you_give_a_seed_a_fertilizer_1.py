# --- Day 5: If You Give A Seed A Fertilizer ---

if __name__ == '__main__':
    file = open("if_you_give_a_seed_a_fertilizer_input", "r")
    lines = file.readlines()

    categories = ("seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light",
                  "light-to-temperature", "temperature-to-humidity", "humidity-to-location")

    maps = {"seed-to-soil": [], "soil-to-fertilizer": [], "fertilizer-to-water": [], "water-to-light": [],
            "light-to-temperature": [], "temperature-to-humidity": [], "humidity-to-location": []}

    current_category = "seeds:"
    seeds = []

    for line in lines:
        parts = line.split()

        if len(parts) > 0:
            if parts[0] == "seeds:":
                for part in parts[1:]:
                    seeds.append(int(part))
            elif parts[0] in maps:
                current_category = parts[0]
            else:
                destination_range = range(int(parts[0]), int(parts[0]) + int(parts[2]))
                source_range = range(int(parts[1]), int(parts[1]) + int(parts[2]))
                maps[current_category].append((destination_range, source_range))

    locations = []
    for seed in seeds:
        value = seed
        for category in categories:
            for translate in maps[category]:
                if value in translate[1]:
                    value = translate[0][translate[1].index(value)]
                    break
        locations.append(value)

    locations.sort()
    print(locations[0])
