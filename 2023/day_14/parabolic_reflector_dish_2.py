# --- Day 14: Parabolic Reflector Dish --- Part Two ---

def spin_cycle(dish) -> tuple:
    dish_list = list(map(list, dish))
    for _ in range(4):
        for line in dish_list:
            last = 0
            for i, char in enumerate(line):
                if char == "O":
                    line[i] = "."
                    line[last] = "O"
                    last += 1
                elif char == "#":
                    last = i + 1
        dish_list = [list(line) for line in reversed(list(zip(*dish_list)))]
    return tuple(map(tuple, dish_list))


if __name__ == '__main__':
    with open("../../input/2023/day_14/input.txt") as file:
        original_dish = tuple(zip(*file.read().splitlines()))

    dish_states = [original_dish]
    while True:
        new_dish = spin_cycle(dish_states[-1])
        if new_dish in dish_states:
            break
        dish_states.append(new_dish)

    loop_start = dish_states.index(new_dish)
    loop_length = len(dish_states) - loop_start
    rest_rounds = (10 ** 9 - loop_start) % loop_length
    final_dish = dish_states[loop_start + rest_rounds]

    load_on_beams = 0
    for line in final_dish:
        for i, char in enumerate(line):
            if char == 'O':
                load_on_beams += len(line) - i

    print("Part 2:", load_on_beams)
