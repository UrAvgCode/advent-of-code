# --- Day 9: Mirage Maintenance ---

if __name__ == '__main__':
    with open("../../input/2023/day_09/input.txt") as file:
        histories = [[int(num) for num in line.split()] for line in file.read().strip().split("\n")]

    sum_predictions = sum_beginnings = 0
    for history in histories:
        sequences = [history]
        while any(sequences[-1]):
            sequences.append([j - i for i, j in zip(sequences[-1], sequences[-1][1:])])

        sum_predictions += sum(d[-1] for d in reversed(sequences))

        placeholder = 0
        for difference in reversed(sequences):
            placeholder = difference[0] - placeholder
        sum_beginnings += placeholder

    print("Part 1:", sum_predictions)
    print("Part 2:", sum_beginnings)
