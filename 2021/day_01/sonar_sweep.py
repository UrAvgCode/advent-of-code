# --- Day 1: Sonar Sweep ---

if __name__ == "__main__":
    with open("sonar_sweep_input") as file:
        depths = list(map(int, file.read().splitlines()))

    print("Part 1:", sum([last < now for last, now in zip(depths, depths[1:])]))
    print("Part 2:", sum([last < now for last, now in zip(depths, depths[3:])]))
