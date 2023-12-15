# --- Day 14: Parabolic Reflector Dish --- Part One ---

if __name__ == '__main__':
    with open("parabolic_reflector_dish_input") as file:
        lines = file.read().splitlines()
    dish = [list(line) for line in zip(*lines)]

    weight = 0
    for line in dish:
        last = 0
        for i, char in enumerate(line):
            if char == "O":
                line[i] = "."
                line[last] = "O"
                weight += len(line) - last
                last += 1
            elif char == "#":
                last = i + 1

    print("Part 1:", weight)
