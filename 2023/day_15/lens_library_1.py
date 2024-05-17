# --- Day 15: Lens Library --- Part One ---

def get_hash(string):
    current_value = 0
    for char in string:
        current_value = ((current_value + ord(char)) * 17) % 256
    return current_value


if __name__ == '__main__':
    with open("../../input/2023/day_15/input.txt") as file:
        lines = file.read().strip().split(',')
    print("Part 1:", sum(get_hash(line) for line in lines))
