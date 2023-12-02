# --- Day 1: Trebuchet?! ---

if __name__ == '__main__':
    file = open("trebuchet_input", "r")
    lines = file.readlines()

    calibration_values_one = 0
    calibration_values_two = 0

    numberStrings = ("one", "two", "three", "four", "five", "six", "seven", "eight", "nine")

    for line in lines:
        firstDigit_one = 0
        secondDigit_one = 0

        firstDigit_two = 0
        secondDigit_two = 0

        for i in range(len(line)):
            for number in numberStrings:
                if line[i:i + len(number)] == number:
                    if firstDigit_two == 0:
                        firstDigit_two = numberStrings.index(number) + 1
                    secondDigit_two = numberStrings.index(number) + 1

            if line[i].isdigit():
                if firstDigit_one == 0:
                    firstDigit_one = int(line[i])
                if firstDigit_two == 0:
                    firstDigit_two = int(line[i])
                secondDigit_one = int(line[i])
                secondDigit_two = int(line[i])

        calibration_values_one += firstDigit_one * 10 + secondDigit_one
        calibration_values_two += firstDigit_two * 10 + secondDigit_two

    print("Part 1: " + str(calibration_values_one))
    print("Part 2: " + str(calibration_values_two))
