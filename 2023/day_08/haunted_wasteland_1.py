# --- Day 8: Haunted Wasteland --- Part One ---

if __name__ == '__main__':
    with open("../../input/2023/day_08/input.txt") as file:
        instructions, lines = file.read().strip().split("\n\n")

    move_map = {}
    lines = lines.split("\n")
    for line in lines:
        parts = line.replace("= (", "").replace(",", "").replace(")", "").split()
        move_map[parts[0]] = (parts[1], parts[2])

    location = "AAA"
    step_counter = 0
    while True:
        current_instruction = instructions[step_counter % len(instructions)]
        if current_instruction == "L":
            location = move_map[location][0]
        else:
            location = move_map[location][1]
        step_counter += 1

        if location == "ZZZ":
            break

    print("Part 1:", step_counter)
