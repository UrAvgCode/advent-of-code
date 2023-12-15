# --- Day 14: Parabolic Reflector Dish --- Part One ---

if __name__ == '__main__':
    with open("parabolic_reflector_dish_input") as file:
        dish = [list(line) for line in zip(*file.read().splitlines())]

    load_on_beams = 0
    for line in dish:
        last = 0
        for i, char in enumerate(line):
            if char == "O":
                line[i] = "."
                line[last] = "O"
                load_on_beams += len(line) - last
                last += 1
            elif char == "#":
                last = i + 1

    print("Part 1:", load_on_beams)
