# --- Day 10: Cathode-Ray Tube ---

if __name__ == '__main__':
    with open("../../input/2022/day_10/input.txt") as file:
        instructions = file.read().splitlines()

    cycles = []
    for instruction in instructions:
        cmd, *add = instruction.split()
        cycles.append(0)
        if add:
            cycles.append(int(*add))

    screen = []
    x_register = 1
    signal_strengths = 0
    for i, cycle in enumerate(cycles):
        screen.append('■' if x_register - 1 <= i % 40 <= x_register + 1 else ' ')

        x_register += cycle
        if (i + 1) % 40 == 20:
            signal_strengths += x_register * (i + 1)

    print("Part 1:", signal_strengths)
    print("Part 2:")
    for i in range(0, len(screen), 40):
        print("".join(screen[i:i + 40]))
