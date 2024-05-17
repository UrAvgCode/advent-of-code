# --- Day 2: Rock Paper Scissors ---

if __name__ == '__main__':
    with open("../../input/2022/day_02/input.txt") as file:
        rounds = file.read().strip().split("\n")

    first_strategy = {"A Y": 8, "B Z": 9, "C X": 7, "A X": 4, "B Y": 5, "C Z": 6, "A Z": 3, "B X": 1, "C Y": 2}
    correct_strategy = {"A X": 3, "B X": 1, "C X": 2, "A Y": 4, "B Y": 5, "C Y": 6, "A Z": 8, "B Z": 9, "C Z": 7}

    score_one = sum(first_strategy[match] for match in rounds)
    score_two = sum(correct_strategy[match] for match in rounds)

    print("Part 1:", score_one)
    print("Part 2:", score_two)
