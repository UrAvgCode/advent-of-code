# --- Day 10: Cathode-Ray Tube ---

if __name__ == '__main__':
    file = open("cathode-ray_tube_input", "r")
    lines = file.readlines()

    cycle_list = []
    for line in lines:
        parts = line.split()
        cycle_list.append(0)
        if parts[0] == "addx":
            cycle_list.append(int(parts[1]))

    x_register = 1
    signal_strengths = 0
    screen = []

    for i in range(len(cycle_list)):
        if x_register - 1 <= i % 40 <= x_register + 1:
            screen.append("#")
        else:
            screen.append(" ")

        cycle = i + 1
        x_register += cycle_list[i]
        if cycle == 20 or cycle == 60 or cycle == 100 or cycle == 140 or cycle == 180 or cycle == 220:
            signal_strengths += x_register * cycle

    print("Part 1: " + str(signal_strengths))
    print("Part 2: ")
    for i in range(0, len(screen), 40):
        print("".join(screen[i:i + 40]))
