# --- Day 1: Sonar Sweep ---

if __name__ == "__main__":
    with open("../../input/2021/day_01/input.txt") as file:
        depths = list(map(int, file.read().splitlines()))

    print("Part 1:", sum([last < now for last, now in zip(depths, depths[1:])]))
    print("Part 2:", sum([last < now for last, now in zip(depths, depths[3:])]))
