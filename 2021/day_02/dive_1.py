# --- Day 2: Dive! --- Part One ---

if __name__ == '__main__':
    with open('dive_input') as file:
        lines = [line.split() for line in file.read().splitlines()]

    depth = 0
    horizontal_position = 0
    for command, amount in lines:
        if command == 'forward':
            horizontal_position += int(amount)
        elif command == 'up':
            depth -= int(amount)
        elif command == 'down':
            depth += int(amount)

    print('Part 1:', depth * horizontal_position)
