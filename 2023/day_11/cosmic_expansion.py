# --- Day 11: Cosmic Expansion ---

def get_distances(expansion):
    galaxy_list = []
    for y, row in enumerate(galaxy_map):
        for x, char in enumerate(row):
            if char == "#":
                galaxy_list.append((x, y))

    distances = 0
    while galaxy_list:
        first = galaxy_list.pop()
        for second in galaxy_list:
            distances += abs(first[0] - second[0]) + abs(first[1] - second[1])

            for i in empty_rows:
                if first[1] < i < second[1] or second[1] < i < first[1]:
                    distances += expansion - 1

            for i in empty_cols:
                if first[0] < i < second[0] or second[0] < i < first[0]:
                    distances += expansion - 1

    return distances


if __name__ == '__main__':
    with open("cosmic_expansion_input") as file:
        galaxy_map = file.read().strip().split("\n")

    empty_rows = []
    for y, row in enumerate(galaxy_map):
        if all(char == "." for char in row):
            empty_rows.append(y)

    empty_cols = []
    for x in range(len(galaxy_map[0])):
        if all(galaxy_map[y][x] == "." for y in range(len(galaxy_map))):
            empty_cols.append(x)

    print("Part 1:", get_distances(2))
    print("Part 2:", get_distances(1000000))
