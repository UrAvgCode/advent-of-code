# --- Day 2: Rock Paper Scissors ---

if __name__ == '__main__':
    file = open("rock_paper_scissors_input", "r")
    lines = file.readlines()

    first_tactic = {"A Y": 8, "B Z": 9, "C X": 7, "A X": 4, "B Y": 5, "C Z": 6, "A Z": 3, "B X": 1, "C Y": 2}
    correct_tactic = {"A X": 3, "B X": 1, "C X": 2, "A Y": 4, "B Y": 5, "C Y": 6, "A Z": 8, "B Z": 9, "C Z": 7}

    score_one = 0
    score_two = 0
    for line in lines:
        score_one += first_tactic[line.strip()]
        score_two += correct_tactic[line.strip()]

    print("Part 1: " + str(score_one))
    print("Part 2: " + str(score_two))
