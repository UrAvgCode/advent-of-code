# --- Day 4: Scratchcards ---

if __name__ == '__main__':
    with open("scratchcards_input") as file:
        lines = file.read().splitlines()

    total_points = 0
    scratchcards = [1] * len(lines)

    for card_num, line in enumerate(lines):
        left, right = line.split("|")
        winning_numbers = set(map(int, left.split()[2:]))
        my_numbers = set(map(int, right.split()))

        matches = len(my_numbers & winning_numbers)
        if matches:
            total_points += 2 ** (matches - 1)

        for i in range(card_num + 1, min(card_num + matches + 1, len(scratchcards))):
            scratchcards[i] += scratchcards[card_num]

    print("Part 1:", total_points)
    print("Part 2:", sum(scratchcards))
