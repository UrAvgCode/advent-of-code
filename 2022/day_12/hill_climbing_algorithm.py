# --- Day 12: Hill Climbing Algorithm ---

abc = "abcdefghijklmnopqrstuvwxyz"


def height(char):
    if char == 'S':
        return 0
    elif char == 'E':
        return 25
    elif char != '\n':
        return abc.index(char)
    else:
        return 100


def find_shortest_path(start):
    move_queue = [start]
    visited = set()

    while True:
        if len(move_queue) == 0:
            return -1
        move = move_queue.pop(0)
        x = move[0]
        y = move[1]
        moves = move[2]

        if lines[y][x] == 'E':
            return moves

        if (x, y) in visited:
            continue
        visited.add((x, y))

        if x < len(lines[y]) - 1 and height(lines[y][x]) >= height(lines[y][x + 1]) - 1:
            move_queue.append((x + 1, y, moves + 1))
        if x > 0 and height(lines[y][x]) >= height(lines[y][x - 1]) - 1:
            move_queue.append((x - 1, y, moves + 1))
        if y != 0 and height(lines[y][x]) >= height(lines[y - 1][x]) - 1:
            move_queue.append((x, y - 1, moves + 1))
        if y != len(lines) - 1 and height(lines[y][x]) >= height(lines[y + 1][x]) - 1:
            move_queue.append((x, y + 1, moves + 1))


if __name__ == '__main__':
    file = open("hill_climbing_algorithm_input", "r")
    lines = file.readlines()

    distance_from_start = -1
    distances = []
    for i in range(len(lines)):
        for j in range(len(lines[i])):
            if lines[i][j] == 'a' or lines[i][j] == 'S':
                distance = find_shortest_path((j, i, 0))
                if distance != -1:
                    distances.append(distance)
                    if lines[i][j] == 'S':
                        distance_from_start = distance

    print("Part 1: " + str(distance_from_start))
    print("Part 2: " + str(min(distances)))
