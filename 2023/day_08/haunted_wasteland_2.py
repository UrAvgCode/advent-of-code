# --- Day 8: Haunted Wasteland --- Part Two ---

import math

if __name__ == '__main__':
    with open("../../input/2023/day_08/input.txt") as file:
        instructions, lines = file.read().strip().split("\n\n")

    move_map = {}
    for line in lines.replace("= (", "").replace(",", "").replace(")", "").split("\n"):
        parts = line.split()
        move_map[parts[0]] = (parts[1], parts[2])

    locations = []
    for key in move_map:
        if key[-1] == "A":
            locations.append(key)

    step_counters = []
    for i in range(len(locations)):
        step_counter = 0
        while True:
            current_instruction = instructions[step_counter % len(instructions)]
            if current_instruction == "L":
                locations[i] = move_map[locations[i]][0]
            else:
                locations[i] = move_map[locations[i]][1]
            step_counter += 1

            if locations[i].endswith("Z"):
                step_counters.append(step_counter)
                break

    print("Part 2:", math.lcm(*step_counters))
