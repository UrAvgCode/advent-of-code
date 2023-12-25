# --- Day 2: Dive! --- Part Two ---

if __name__ == '__main__':
    with open('dive_input') as file:
        lines = [line.split() for line in file.read().splitlines()]

    aim = 0
    depth = 0
    horizontal_position = 0
    for command, amount in lines:
        if command == 'forward':
            depth += aim * int(amount)
            horizontal_position += int(amount)
        elif command == 'up':
            aim -= int(amount)
        elif command == 'down':
            aim += int(amount)

    print('Part 2:', depth * horizontal_position)
