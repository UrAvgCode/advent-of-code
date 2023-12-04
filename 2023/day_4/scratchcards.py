# --- Day 4: Scratchcards ---

if __name__ == '__main__':
    file = open("scratchcards_input", "r")
    lines = file.readlines()

    score = 0
    count = 0
    scratchcards = [1 for i in range(len(lines))]

    for card_num in range(len(lines)):
        parts = lines[card_num].split("|")
        left = parts[0].split()[2:]
        right = parts[1].split()

        winning_numbers = set()
        my_numbers = set()

        for number in left:
            winning_numbers.add(int(number))
        for number in right:
            my_numbers.add(int(number))

        matches = len(my_numbers.intersection(winning_numbers))

        if matches > 0:
            score += 2 ** (matches - 1)

        for i in range(card_num + 1, card_num + matches + 1):
            if i < len(scratchcards):
                scratchcards[i] += scratchcards[card_num]

    for i in range(len(scratchcards)):
        count += scratchcards[i]

    print("Part 1: ", score)
    print("Part 2: ", count)
