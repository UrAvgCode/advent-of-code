# --- Day 14: Parabolic Reflector Dish --- Part Two ---

def spin_cycle(dish):
    dish_list = [list(line) for line in dish]
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
        dish_list = [list(line) for line in list(zip(*dish_list))[::-1]]
    return tuple(map(tuple, dish_list))


if __name__ == '__main__':
    with open("parabolic_reflector_dish_input") as file:
        original_dish = tuple(zip(*file.read().splitlines()))

    dish_dict = {}
    loop_dish = ()
    new_dish = original_dish
    while True:
        previous_dish = new_dish
        if previous_dish not in dish_dict:
            new_dish = spin_cycle(new_dish)
            dish_dict[previous_dish] = new_dish
        else:
            loop_dish = previous_dish
            break

    before_loop = 0
    new_dish = original_dish
    while True:
        previous_dish = new_dish
        if previous_dish == loop_dish:
            break
        else:
            before_loop += 1
            new_dish = dish_dict.pop(previous_dish)

    rest_rounds = (10 ** 9 - before_loop) % len(dish_dict)

    result_element = list(dish_dict.keys())[rest_rounds]

    weight = 0
    for line in result_element:
        for i, char in enumerate(line):
            if char == 'O':
                weight += len(line) - i

    print("Part 2:", weight)
