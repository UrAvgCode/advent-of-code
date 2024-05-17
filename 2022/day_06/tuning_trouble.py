# --- Day 6: Tuning Trouble ---

def find_marker(length):
    for i in range(len(datastream)):
        if len(set(datastream[i:i + length])) == length:
            return i + length


if __name__ == '__main__':
    with open("../../input/2022/day_06/input.txt") as file:
        datastream = file.read()

    print("Part 1:", find_marker(4))
    print("Part 2:", find_marker(14))
