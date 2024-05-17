# --- Day 1: Trebuchet?! ---

def get_calibration_values(digit_words):
    calibration_values = 0
    for line in lines:
        first_digit = last_digit = 0

        for i, char in enumerate(line):
            if char.isdigit():
                last_digit = int(char)
                if first_digit == 0:
                    first_digit = last_digit
            elif digit_words:
                for digit_word, digit_value in digit_words:
                    if line[i:i + len(digit_word)] == digit_word:
                        last_digit = digit_value
                        if first_digit == 0:
                            first_digit = digit_value
                        break

        calibration_values += first_digit * 10 + last_digit

    return calibration_values


if __name__ == '__main__':
    with open("../../input/2023/day_01/input.txt") as file:
        lines = file.read().splitlines()

    digit_words = [(item, i) for i, item in enumerate("one two three four five six seven eight nine".split(), 1)]

    print("Part 1:", get_calibration_values([]))
    print("Part 2:", get_calibration_values(digit_words))
